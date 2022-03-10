/*
   log_manager.h
   © 2020 Vizio Services, All Rights Reserved
    Log Manager handles the log levels for each module. Log manager receives events to dynamically change
    the log levels for a given module.

*/

#pragma once
#include <map>
#include <string>
#include <thread>

class LogManager
{
private:
    LogManager()
    {
    }

    LogManager(LogManager &&) = delete;

    std::map<std::string, int> module_map; //Module names and run_time log level
    std::mutex module_map_mutex;

    void set_runtime_log_level(std::string module, int runtime_level)
    {
        std::unique_lock<std::mutex> lock(module_map_mutex);
        
        if (module == "")
        {
            for (auto &module : module_map)
            {
                module.second = runtime_level;
            }
            lock.unlock();
            return;
        }

        auto itr = module_map.find(module);
        if (itr != module_map.end())
            itr->second = runtime_level;
        lock.unlock();
    }

public:
    static LogManager &get_instance()
    {
        static LogManager instance;
        return instance;
    }

    ~LogManager()
    {
    }

    void add_module(std::string module, int runtime_level)
    {
        std::unique_lock<std::mutex> lock(module_map_mutex);
        module_map.insert({module, runtime_level});
        lock.unlock();
    }

    int get_runtime_log_level(std::string module)
    {
        std::unique_lock<std::mutex> lock(module_map_mutex);
        auto itr = module_map.find(module);
        if (itr != module_map.end())
        {
            lock.unlock();
            return itr->second;
        }
        lock.unlock();
        return 0;
    }
};