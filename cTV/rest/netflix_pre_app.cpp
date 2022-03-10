#include <iostream>

#include "common.h"
#include "rest/a_rest_event.h"

#include "netflix_pre_app.h"
#include "MtkDtvTileManager.h"

using namespace netflix;

class CsTileManager : public MtkDtvTileManager{
public:

    CsTileManager(){
        pthread_mutex_init(&mTilesMutex, NULL);
        pthread_cond_init(&mTilesCond, NULL);
    }

    ~CsTileManager(){
        pthread_mutex_destroy(&mTilesMutex);
        pthread_cond_destroy(&mTilesCond);
    }

    virtual void MtkError(const std::string & e) override {
        fprintf(stderr,"[Tile] mtk error = %s\n", e.c_str());
    }
    virtual void MtkInotifyActivated() override {
        fprintf(stderr,"[Tile] mtk inotify Activated\n");
    }
    virtual void MtkTilesChanged() override;

    void getTiles(Tiles &tiles){
        pthread_mutex_lock(&mTilesMutex);
    //    pthread_cond_wait(&mTilesCond, &mTilesMutex);
        tiles = mTiles;
        pthread_mutex_unlock(&mTilesMutex);
    }

private:
    void setTiles(const Tiles &tiles){
        pthread_mutex_lock(&mTilesMutex);
        mTiles = tiles;
   //     pthread_cond_signal(&mTilesCond);
        pthread_mutex_unlock(&mTilesMutex);
    }

private:
    Tiles mTiles;
    pthread_mutex_t mTilesMutex ;
    pthread_cond_t mTilesCond ;
};

CsTileManager *mTileManager = NULL;

void CsTileManager::MtkTilesChanged(){
    REST_LOG_I("[Tile] mtk tiles Changed\n");
    setTiles(MtkDtvTileManager::getTiles());
    /* MVV-8245 : Remove notify because netflix metadata is not used by SCPL
    rest_event_notify("app/metadata", 0, "preAppData");
    */
}

int Get_pre_app_data(Json::Value & response)
{
    REST_LOG_I("[Tile] get app data enter\r\n");
    Json::Value tiles_data, groups_data;
    Json::Value tile_data, group_data, PreAppData;
    int tile_count, group_count;
    TileManager::Tiles tiles;

    mTileManager->getTiles(tiles);
    Tile::Value ret = tiles.value;
    const time_t now = mTileManager->getCurrentTime();

    if (0 == access("/3rd_rw/netflix/nrd-app/data/var/nrd/activated", F_OK))
    {
        response["REGISTERED"] = std::string("Registered");
    }
    else
    {
        response["REGISTERED"] = std::string("Unknown");
    }

    response["NAME_SPACE"] = 3;
    response["APP_ID"] = std::string("1");

    group_count = 0;
    for (auto &group : ret.object["groups"].array) {

        group_data["groupIndex"]    = group.object["groupIndex"].integer;
        group_data["groupType"]     = group.object["groupType"].string;

        auto &tiles = group.object["tiles"].array;
        auto it = tiles.begin();
        tile_count = 0;
        while (it != tiles.end()) {
            tile_data["deepLink"]    = it->object["deepLink"].string;
            tile_data["expiry"]      = (long long int)(static_cast<time_t>(it->object["expiry"].integer) - now);
            tile_data["url"]         = it->object["url"].string;
            tile_data["height"]      = it->object["height"].integer;
            tile_data["width"]       = it->object["width"].integer;
            tile_data["shortText"]   = it->object["shortText"].string;

            tiles_data[tile_count++] = tile_data;
            ++it;
        }
        group_data["tiles"] = tiles_data;
        group_data["title"] = group.object["title"].string;

        groups_data[group_count++] = group_data;
    }
    if (group_count != 0)
        PreAppData["groups"] = groups_data;
    response["METADATA"] = PreAppData;

    return 0;
}

int pre_app_init()
{
    REST_LOG_I("Enter\r\n");
    TileManager::Tiles  tiles;
    mTileManager = new CsTileManager;
    mTileManager->startMonitor(20000);

    return 0;
}

int pre_app_deinit()
{
    mTileManager->stopMonitor();
    delete mTileManager;
    return 0;
}

