#! /usr/bin/perl

#define constant
$FMT_UTF16_NEW_LINE = "\x{000d}\x{000a}";
$FMT_UTF8_NEW_LINE = "\n";
$FILE_FMT_UTF16_HEADER = "\x{FEFF}";
$FILE_FMT_UTF8_HEADER = "";
$FILE_FMT_UTF16_CREATE_ENCODING = ">:raw:encoding(UTF-16LE)";
$FILE_FMT_UTF8_CREATE_ENCODING = ">:raw:encoding(utf8)";
$FILE_FMT_UTF16_APPEND_ENCODING = ">>:raw:encoding(UTF-16LE)";
$FILE_FMT_UTF8_APPEND_ENCODING = ">>:raw:encoding(utf8)";

#
$IMAGE_CONFIG_SECTION_TOKEN = "[General]";
$IMAGE_CONFIG_OUTPUT_TOKEN = "OUTPUT_FILE";
$IMAGE_CONFIG_TEMP_CONVERTED_FILE = "converted_file.txt";
$IMAGE_CONFIG_BMP_BITS_PREFIX_1 = "__align(4) static UINT8 ";
$IMAGE_CONFIG_BMP_BITS_PREFIX_2 = "[] = \n{\n";

$IMAGE_CONFIG_BMP_CLUT_BITS_PREFIX_1 = "static GL_COLOR_T ";
$IMAGE_CONFIG_BMP_CLUT_BITS_PREFIX_2 = "[] = \n{\n";

$IMAGE_CONFIG_VARIABLE_PREFIX_1 = "WGL_IMG_T ";
$IMAGE_CONFIG_VARIABLE_PREFIX_2 = " = \n{\n";
$IMAGE_CONFIG_VARIABLE_RPEFIX_3 = "extern ";
$IMAGE_CONFIG_VARIABLE_EXT = "_bits";



$IMAGE_CONFIG_POSTFIX = "};\n\n";
$IMAGE_CONFIG_POSTFIX_2 = ";\n";

#global variable
$CURRENT_FOLDER;
%FILE_PATH_TABLE;
%FILE_PREFIX_TABLE;
$FILE_POSTFIX_TABLE;
%FILE_FORMAT_TABLE;
$FILE_POSTFIX_CLUT_TABLE;

%SECTION_FILE_TABLE;
%SECTION_PREFIX_TABLE;
%SECTION_POSTFIX_TABLE;
%SECTION_FORMAT_TABLE;
%SECTION_COMMAND2CHILD_TABLE;
$SECTION_CHILD_PREFIX_TABLE;
$SECTION_CHILD_POSTFIX_TABLE;
%SECTION_CHILD_TABLE;
%MAP_ID_TABLE;
%VALUE_TABLE;

%IMAGE_CONFIG_TABLE;
%IMAGE_CONVERTED_TABLE;
%IMAGE_VARIABLE_NAME_TABLE;
%IMAGE_IMPLEMENT_FILE_TABLE;
%IMAGE_HEADER_FILE_TABLE;

#main function
print ("GUI Code Generator is starting...\n");

$CURRENT_FOLDER = Win32::GetCwd;
print ("Current Folder = $CURRENT_FOLDER\n");
$IMAGE_CONFIG_TEMP_CONVERTED_FILE = "$CURRENT_FOLDER\\$IMAGE_CONFIG_TEMP_CONVERTED_FILE";
print ("Temp file = $IMAGE_CONFIG_TEMP_CONVERTED_FILE\n");

print ("Parsing Map Table\n");
parse_map_table();

print ("Parsing Variable File\n");
parse_variable_file();

print ("Output result...\n");
generate_output();

#visit_tables();
print ("GUI Code Generator is completed.\n");


sub visit_tables
{
	my ($one);
	
	print "FILE_PATH_TABLE...\n";
	foreach $one (keys(%FILE_PATH_TABLE))
	{
		print $FILE_PATH_TABLE{$one}, "\n";
	}
	
	print "FILE_PREFIX_TABLE...\n";
	foreach $one (keys(%FILE_PREFIX_TABLE))
	{
		print $FILE_PREFIX_TABLE{$one}, "\n";
	}
	
	print "FILE_FORMAT_TABLE...\n";
	foreach $one (keys(%FILE_FORMAT_TABLE))
	{
		print $FILE_FORMAT_TABLE{$one}, "\n";
	}
	
	print "SECTION_FILE_TABLE...\n";
	foreach $one (keys(%SECTION_FILE_TABLE))
	{
		print $SECTION_FILE_TABLE{$one}, "\n";
	}
	
	print "SECTION_PREFIX_TABLE...\n";
	foreach $one (keys(%SECTION_PREFIX_TABLE))
	{
		print $SECTION_PREFIX_TABLE{$one}, "\n";
	}
	
	print "SECTION_CHILD_TABLE...\n";
	foreach $one (keys(%SECTION_CHILD_TABLE))
	{
		print $SECTION_CHILD_TABLE{$one}, "\n";
	}
	
	print "MAP_ID_TABLE...\n";
	foreach $one (keys(%MAP_ID_TABLE))
	{
		print $MAP_ID_TABLE{$one}, "\n";
	}
	
	print "IMAGE_CONVERTED_TABLE...\n";
	foreach $one (keys(%IMAGE_CONVERTED_TABLE))
	{
		print $IMAGE_CONVERTED_TABLE{$one}, "\n";
	}
	
	print "IMAGE_CONFIG_TABLE...\n";
	foreach $one (keys(%IMAGE_CONFIG_TABLE))
	{
		print $IMAGE_CONFIG_TABLE{$one}, "\n";
	}
	
	print "IMAGE_VARIABLE_NAME_TABLE...\n";
	foreach $one (keys(%IMAGE_VARIABLE_NAME_TABLE))
	{
		print $IMAGE_VARIABLE_NAME_TABLE{$one}, "\n";
	}
	
	print "IMAGE_IMPLEMENT_FILE_TABLE...\n";
	foreach $one (keys(%IMAGE_IMPLEMENT_FILE_TABLE))
	{
		print $IMAGE_IMPLEMENT_FILE_TABLE{$one}, "\n";
	}
	
	print "IMAGE_HEADER_FILE_TABLE...\n";
	foreach $one (keys(%IMAGE_HEADER_FILE_TABLE))
	{
		print $IMAGE_HEADER_FILE_TABLE{$one}, "\n";
	}

}

sub remove_space
{
	my ($id);
	$id = $_[0];
	
	if($id =~ /(\s*)(\w+)(\s*)/)	
	{
		return $2;	
	}
	else
	{
		return "";
	}
}

sub generate_output
{	
	my ($image_config_id);
	my ($file_id);
	
	foreach $file_id (keys(%FILE_PATH_TABLE))
	{
		output_file_title($file_id, $FILE_PATH_TABLE{$file_id});
	}
	
	foreach $file_id (keys(%FILE_PATH_TABLE))
	{
		output_file_body($file_id, $FILE_PATH_TABLE{$file_id});
	}
	
	foreach $image_config_id (keys(%IMAGE_VARIABLE_NAME_TABLE))
	{
		print "Convert $image_config_id...\n";
		convert_image_file($image_config_id);
	}
	
	foreach $file_id (keys(%FILE_PATH_TABLE))
	{
		output_file_tail($file_id, $FILE_PATH_TABLE{$file_id});
	}
}

sub output_file_title
{
	my ($result);
	my ($file_id);
	my ($file_name);
	my (@section_list);
	my ($section_id);
	my ($open_format);
	my ($file_header);
	my ($new_line);
	
	$file_id = $_[0];
	$file_name = $_[1];
	
	print "Generate...'$file_name'\n";
	
	if($FILE_FORMAT_TABLE{$file_id} eq "MLM")
	{
		$open_format = $FILE_FMT_UTF16_CREATE_ENCODING;
		$file_header = $FILE_FMT_UTF16_HEADER;
		$new_line = $FMT_UTF16_NEW_LINE;
	}
	else
	{
		$open_format = $FILE_FMT_UTF8_CREATE_ENCODING;
		$file_header = $FILE_FMT_UTF8_HEADER;
		$new_line = $FMT_UTF8_NEW_LINE;
	}
	
	#open output file
	$result = open (H_OUTPUT_FILE, $open_format, $file_name);
	if(!$result)
	{
		die "Fail to open file, because...($!) \n";
	}
	
	#output file header
	print H_OUTPUT_FILE $file_header;
	
	#output file prefix
	if($FILE_PREFIX_TABLE{$file_id})
	{
		if($new_line == $FMT_UTF8_NEW_LINE)
		{
			$FILE_PREFIX_TABLE{$file_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
		}
		print H_OUTPUT_FILE $FILE_PREFIX_TABLE{$file_id}, $new_line;
		
		#add a new line between file-prefix and sections
		print H_OUTPUT_FILE $new_line;
	}
	
	#close output file
	$result = close(H_OUTPUT_FILE);
	if(!$result)
	{
		die "Fail to close file, because...($!) \n";
	}
}

sub output_file_body
{
	my ($result);
	my ($file_id);
	my ($file_name);
	my (@section_list);
	my ($section_id);
	my ($open_format);
	my ($file_header);
	my ($new_line);
	
	$file_id = $_[0];
	$file_name = $_[1];
	
	if($FILE_FORMAT_TABLE{$file_id} eq "MLM")
	{
		$open_format = $FILE_FMT_UTF16_APPEND_ENCODING;
		$file_header = $FILE_FMT_UTF16_HEADER;
		$new_line = $FMT_UTF16_NEW_LINE;
	}
	else
	{
		$open_format = $FILE_FMT_UTF8_APPEND_ENCODING;
		$file_header = $FILE_FMT_UTF8_HEADER;
		$new_line = $FMT_UTF8_NEW_LINE;
	}
	
	#open output file
	$result = open (H_OUTPUT_FILE, $open_format, $file_name);
	if(!$result)
	{
		die "Fail to open file, because...($!) \n";
	}
	
	#output section
	@section_list = split(/;/, $SECTION_FILE_TABLE{$file_id});
	foreach $section_id (@section_list)
	{
		output_section_data($section_id, *H_OUTPUT_FILE, $new_line);
	}
	
	#close output file
	$result = close(H_OUTPUT_FILE);
	if(!$result)
	{
		die "Fail to close file, because...($!) \n";
	}
}

sub output_file_tail
{
	my ($result);
	my ($file_id);
	my ($file_name);
	my ($open_format);
	my ($file_header);
	my ($new_line);
	
	$file_id = $_[0];
	$file_name = $_[1];
	
	if($FILE_FORMAT_TABLE{$file_id} eq "MLM")
	{
		$open_format = $FILE_FMT_UTF16_APPEND_ENCODING;
		$file_header = $FILE_FMT_UTF16_HEADER;
		$new_line = $FMT_UTF16_NEW_LINE;
	}
	else
	{
		$open_format = $FILE_FMT_UTF8_APPEND_ENCODING;
		$file_header = $FILE_FMT_UTF8_HEADER;
		$new_line = $FMT_UTF8_NEW_LINE;
	}
	
	#open output file
	$result = open (H_OUTPUT_FILE, $open_format, $file_name);
	if(!$result)
	{
		die "Fail to open file, because...($!) \n";
	}
	
	#output file postfix
	if($FILE_POSTFIX_TABLE{$file_id})
	{
		#add a new line between sections and file-postfix
		print H_OUTPUT_FILE $new_line;
		
		if($new_line == $FMT_UTF8_NEW_LINE)
		{
			$FILE_POSTFIX_TABLE{$file_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
		}
		print H_OUTPUT_FILE $FILE_POSTFIX_TABLE{$file_id}, $new_line;
	}
	
	#close output file
	$result = close(H_OUTPUT_FILE);
	if(!$result)
	{
		die "Fail to close file, because...($!) \n";
	}
}

sub output_section_data
{
	my ($section_id);
	my ($file_handle);
	my ($new_line);
	
	$section_id = $_[0];
	$file_handle = $_[1];
	$new_line = $_[2];
	
	#output section's prefix
	if($SECTION_PREFIX_TABLE{$section_id})
	{
		if($new_line == $FMT_UTF8_NEW_LINE)
		{
			$SECTION_PREFIX_TABLE{$section_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
		}
		
		print $file_handle "$SECTION_PREFIX_TABLE{$section_id}";
	}
	
	#output variables of a section
	if(!defined($SECTION_FORMAT_TABLE{$section_id}))
	{
		output_section_child_general($section_id, $file_handle, $new_line);
	}
	elsif($SECTION_FORMAT_TABLE{$section_id} eq "STRUCT")
	{
		output_section_child_struct($section_id, $file_handle, $new_line);
	}
	
	#output section's postfix
	if($SECTION_POSTFIX_TABLE{$section_id})
	{
		if($new_line == $FMT_UTF8_NEW_LINE)
		{
			$SECTION_POSTFIX_TABLE{$section_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
		}
		
		print $file_handle "$SECTION_POSTFIX_TABLE{$section_id}";
	}
	
	#add a new line between two sections
	print $file_handle $new_line;
}

sub output_section_child_general
{
	my (@section_child_list);
	my ($variable_id);
	my ($section_id);
	my ($file_handle);
	my ($new_line);
	
	$section_id = $_[0];
	$file_handle = $_[1];
	$new_line = $_[2];
	
	#output variables of a section
	@section_child_list = split(/;/, $SECTION_CHILD_TABLE{$section_id});
	foreach $variable_id (@section_child_list)
	{
		output_variable_data($variable_id, $file_handle, $section_id, undef, $new_line);
	}
}

sub output_section_child_struct
{
	my (@section_child_list);
	my ($variable_id);
	my ($section_id);
	my ($file_handle);
	my ($section_format);
	my ($new_line);
	
	$section_id = $_[0];
	$file_handle = $_[1];
	$new_line = $_[2];
	
	#get variable-id list of a section
	@section_child_list = split(/;/, $SECTION_CHILD_TABLE{$section_id});
	
	#sort variable-id list
	@section_child_list = sort by_variable_map_id @section_child_list;
	
	#output variables of a section
	$section_format = $SECTION_FORMAT_TABLE{$section_id};
	foreach $variable_id (@section_child_list)
	{
		output_variable_data($variable_id, $file_handle, $section_id, $section_format, $new_line);
	}
}

sub by_variable_map_id
{
	my ($map_id_of_a);
	my ($map_id_of_b);
	
	$map_id_of_a = $MAP_ID_TABLE{$a};
	$map_id_of_b = $MAP_ID_TABLE{$b};
	
	$map_id_of_a <=> $map_id_of_b;
}

sub output_variable_data
{
	my ($variable_id);
	my ($file_handle);
	my ($map_id);
	my ($value);
	my ($prefix);
	my ($postfix);
	my ($parent_id);
	my ($variable_format);
	my ($new_line);
	my ($command_to_variable);
	
	$variable_id = $_[0];
	$file_handle = $_[1];
	$parent_id = $_[2];
	$variable_format = $_[3];
	$new_line = $_[4];
	
	#output variable map-id
	$map_id = $MAP_ID_TABLE{$variable_id};
	$value = $VALUE_TABLE{$variable_id};
	
	if($new_line == $FMT_UTF8_NEW_LINE)
	{
		$SECTION_CHILD_PREFIX_TABLE{$parent_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
		$SECTION_CHILD_POSTFIX_TABLE{$parent_id} =~ s/$FMT_UTF16_NEW_LINE/$new_line/g;
	}
	
	$prefix = $SECTION_CHILD_PREFIX_TABLE{$parent_id};
	$postfix = $SECTION_CHILD_POSTFIX_TABLE{$parent_id};
	$command_to_variable = $SECTION_COMMAND2CHILD_TABLE{$parent_id};
	
	if(defined($map_id) && $map_id =~ /\w+/)
	{
		if(defined($command_to_variable))
		{
			#print $command_to_variable;
			$_ = $value;
			eval $command_to_variable;
			$value = $_;
		}
		
		if($variable_format eq "STRUCT")
		{
			print $file_handle "$prefix$value$postfix", $new_line;
		}
		else
		{
			print $file_handle "$prefix$map_id=$value$postfix", $new_line;
		}
	}
}

sub is_file_mark
{
	my ($line);
	$line = $_[0];
	
	if($line =~ /\[FILE(\s*)=(.*)\]/)
	{
		return remove_space($2);
	}
	else
	{
		return undef;
	}
}

sub is_section_mark
{
	my ($line);
	$line = $_[0];
	
	if($line =~ /\[SECTION(\s*)=(.*)\]/)
	{
		return remove_space($2);
	}
	else
	{
		return undef;
	}
}

sub is_variable_mark
{
	my ($line);
	$line = $_[0];
	
	if($line =~ /\[VARIABLE_BELONG(\s*)=(.*)\]/)
	{
		return remove_space($2);
	}
	else
	{
		return undef;
	}
}

sub is_image_mark
{
	my ($line);
	$line = $_[0];
	
	if($line =~ /\[(\s*)IMAGE_CONFIG(\s*)=(\s*)(.*)\]/)
	{
		print $4."\n";
		return remove_space($4);
	}
	else
	{
		return undef;
	}
}

sub parse_file_desc
{
	my ($file_id);
	my ($line);
	$file_id = $_[0];
	$line = $_[1];
	
	if($line =~ /(\s*)\bPATH\b(\s*)=(\s*)"(.*)"/)
	{
		$FILE_PATH_TABLE{$file_id} = $4;
	}
	elsif($line =~ /(\s*)\bPREFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$FILE_PREFIX_TABLE{$file_id} .= $4 . $FMT_UTF16_NEW_LINE;
	}
	elsif($line =~ /(\s*)\bPOSTFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$FILE_POSTFIX_TABLE{$file_id} .= $4 . $FMT_UTF16_NEW_LINE;
	}
	elsif($line =~ /(\s*)\bFORMAT\b(\s*)=(\s*)"(.*)"/)
	{
		$FILE_FORMAT_TABLE{$file_id} = $4;
	}
	elsif($line =~ /(\s*)\bPOSFIX_CLUT\b(\s*)=(\s*)"(.*)"/)
	{
		$FILE_POSTFIX_CLUT_TABLE{$file_id} = $4;
	}	
}

sub parse_section_desc
{
	my ($section_id);
	my ($line);
	$section_id = $_[0];
	$line = $_[1];
	
	if($line =~ /(\s*)\bFILE\b(\s*)=(\s*)"(.*)"/)
	{
		if($4 ne "") #should enhance
		{
			#$SECTION_FILE_TABLE{$section_id} = $4;
			$SECTION_FILE_TABLE{$4} .= $section_id . ";";
		}
	}
	elsif($line =~ /(\s*)\bPREFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_PREFIX_TABLE{$section_id} .= $4 . $FMT_UTF16_NEW_LINE;
	}
	elsif($line =~ /(\s*)\bPOSTFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_POSTFIX_TABLE{$section_id} .= $4 . $FMT_UTF16_NEW_LINE;
	}
	elsif($line =~ /(\s*)\bFORMAT\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_FORMAT_TABLE{$section_id} = $4;
	}
	elsif($line =~ /(\s*)\bCHILDPREFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_CHILD_PREFIX_TABLE{$section_id} .= $4;
	}
	elsif($line =~ /(\s*)\bCHILDPOSTFIX\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_CHILD_POSTFIX_TABLE{$section_id} .= $4;
	}
	elsif($line =~ /(\s*)\bCOMMAND2CHILD\b(\s*)=(\s*)"(.*)"/)
	{
		$SECTION_COMMAND2CHILD_TABLE{$section_id} = $4;
	}
}

sub parse_variable_desc
{
	my ($parent_id);
	my ($line);
	my ($map_id);
	my ($variable_id);
	
	$parent_id = $_[0];
	$line = $_[1];
	
	if(!defined($parent_id) || $parent_id eq "")
	{
		return;
	}
	
	if($line =~ /(\s*)(\w+)(\s*)=(\s*)"(.*)"/)
	{
		$variable_id = $2;
		$map_id = $5;
		
		$SECTION_CHILD_TABLE{$parent_id} .= $variable_id . ";";
		$MAP_ID_TABLE{$variable_id} = $map_id;
	}
}

sub parse_image_desc
{
	my ($parent_id);
	my ($line);
	
	$parent_id = $_[0];
	$line = $_[1];
	
	if(!defined($parent_id) || $parent_id eq "")
	{
		return;
	}
	
	if($line =~ /(\s*)CONFIG_CONVERTED_FILE(\s*)=(\s*)"(.*)"/)
	{
		$IMAGE_CONVERTED_TABLE{$parent_id} = $4;
	}
	elsif($line =~ /(\s*)CONFIG_VARIABLE_NAME(\s*)=(\s*)"(.*)"/)
	{
		$IMAGE_VARIABLE_NAME_TABLE{$parent_id} = $4;
	}
	elsif($line =~ /(\s*)IMPLEMENT_FILE(\s*)=(\s*)"(.*)"/)
	{
		$IMAGE_IMPLEMENT_FILE_TABLE{$parent_id} = $4;
	}
	elsif($line =~ /(\s*)HEADER_FILE(\s*)=(\s*)"(.*)"/)
	{
		$IMAGE_HEADER_FILE_TABLE{$parent_id} = $4;
	}
	elsif($line =~ /(\s*)SOURCE_FILE(\s*)=(\s*)"\\(.*)"/) #for bmp source in sub folder
	{
	    $IMAGE_CONFIG_TABLE{$parent_id} .= "SOURCE_FILE = " . '"' . "$CURRENT_FOLDER\\$4" . '"' . "\n";
	}
	elsif($line =~ /(\s*)SOURCE_FILE(\s*)=(\s*)"(.*)"/) #for bmp source
	{
	    $IMAGE_CONFIG_TABLE{$parent_id} .= "SOURCE_FILE = " . '"' . "$CURRENT_FOLDER\\$4" . '"' . "\n";
	}
	elsif($line =~ /(\s*)PREVIEW_FILE(\s*)=(\s*)"\\(.*)"/) #for preview file in sub bolder
	{
	    $IMAGE_CONFIG_TABLE{$parent_id} .= "PREVIEW_FILE = " . '"' . "$CURRENT_FOLDER\\$4" . '"' . "\n";
	}
	elsif($line =~ /(\s*)PREVIEW_FILE(\s*)=(\s*)"(.*)"/) #for preview file
	{
	    $IMAGE_CONFIG_TABLE{$parent_id} .= "PREVIEW_FILE = " . '"' . "$CURRENT_FOLDER\\$4" . '"' . "\n";
	}
	else
	{
	    $IMAGE_CONFIG_TABLE{$parent_id} .= $line;
	}
}

sub get_convert_error_string
{
	my ($BCA_OK) = 0;
	my ($BCA_CONFIG_NOT_FOUND) = 1;
	my ($BCA_OPEN_FAIL) = 2;
	my ($BCA_READ_HEADER_FAIL) = 3;
	my ($BCA_OUT_OF_MEMORY) = 4;
	my ($BCA_NOT_BMP) = 5;
	my ($BCA_SEEK_FAIL) = 6;
	my ($BCA_BAD_BITS_SIZE) = 7;
	my ($BCA_READ_BITS_FAIL) = 8;
	my ($BCA_BMP_FMT_NOT_SUP) = 9;
	my ($BCA_OUTPUT_FAIL) = 10;
	my ($BAC_UNKNOWN) = 11;
	
	my ($error_code);
	my ($error_string);
	
	$error_code = $_[0];
	if($BCA_OK == $error_code)
	{
		$error_string = "Success";
	}
	elsif($BCA_CONFIG_NOT_FOUND == $error_code)
	{
		$error_string = "Cannot find the config file";
	}
	elsif($BCA_OPEN_FAIL == $error_code)
	{
		$error_string = "Fail to open the input or output file";
	}
	elsif($BCA_READ_HEADER_FAIL == $error_code)
	{
		$error_string = "Fail to read bitmap's header";
	}
	elsif($BCA_OUT_OF_MEMORY == $error_code)
	{
		$error_string = "Memory is not enough";
	}
	elsif($BCA_NOT_BMP == $error_code)
	{
		$error_string = "Input file isn't a bitmap file";
	}
	elsif($BCA_SEEK_FAIL == $error_code)
	{
		$error_string = "Cannot seek to expected position";
	}
	elsif($BCA_BAD_BITS_SIZE == $error_code)
	{
		$error_string = "Size of the input file is incorrect";
	}
	elsif($BCA_READ_BITS_FAIL == $error_code)
	{
		$error_string = "Fail to read bitmap's pixel data";
	}
	elsif($BCA_BMP_FMT_NOT_SUP == $error_code)
	{
		$error_string = "Input format isn't supported. 16 and 24 bpp is allowed";
	}
	elsif($BCA_OUTPUT_FAIL == $error_code)
	{
		$error_string = "Fail to output data";
	}
	else #$BAC_UNKNOWN
	{
		$error_string = "Unknown error";
	}
	
	return ($error_string);
}

sub convert_image_file
{	
	my ($image_config_id);
	my ($image_config_file);
	my ($ret_value);
	my ($error_string);
	$image_config_id = $_[0];
	
	$image_config_file = "$CURRENT_FOLDER\\image_config.ini";
	
	generate_image_config_file($image_config_id, $image_config_file);
	
	$ret_value = system("BitmapConverter.exe $image_config_file") / 256;
	if(0 != $ret_value)
	{
		($error_string) = get_convert_error_string($ret_value);
		print "[Err]: $IMAGE_VARIABLE_NAME_TABLE{$image_config_id} ----- $error_string\n";
	}
	
	parse_image_converted_file($image_config_id);
}

sub generate_image_config_file
{
	my ($image_config_id);
	my ($image_config_file);
	my ($result);
	
	$image_config_id = $_[0];
	$image_config_file = $_[1];
	
	#open config file
	print "$image_config_file...\n";
	$result = open (H_CONFIG_FILE, ">$image_config_file");
	if(!$result)
	{
		die "Fail to config file, because...($!) \n";
	}
	
	#output SECTION - [General]
	print H_CONFIG_FILE "$IMAGE_CONFIG_SECTION_TOKEN\n";
	
	#output image target IMAGE_CONFIG_TEMP_CONVERTED_FILE
	if(!defined($IMAGE_CONVERTED_TABLE{$image_config_id}))
	{
		$IMAGE_CONVERTED_TABLE{$image_config_id} = $IMAGE_CONFIG_TEMP_CONVERTED_FILE;
	}	
	
	print H_CONFIG_FILE "$IMAGE_CONFIG_OUTPUT_TOKEN = \"$IMAGE_CONVERTED_TABLE{$image_config_id}\"\n";
	
	#output image config
	print H_CONFIG_FILE "$IMAGE_CONFIG_TABLE{$image_config_id}";
	
	close H_CONFIG_FILE;
}

sub parse_image_converted_file
{	
	my ($image_config_id);
	my ($converted_file);
	my ($implement_file);
	my ($header_file);
	my ($image_width);
	my ($image_height);
	my ($pixel_bitcount);
	my ($output_format);
	my ($line);
	my ($result, $result2);
	my ($cur_type);
	my ($bits_variable);
	my ($clut_variable);
	my ($bits_variable_flag);
	my ($clut_variable_flag);
	my ($myClutSize);
	
	$image_config_id = $_[0];
	
	#check variable name
	if(!defined($IMAGE_VARIABLE_NAME_TABLE{$image_config_id}) || !($IMAGE_VARIABLE_NAME_TABLE{$image_config_id} =~ /(\w+)/))
	{
		return;
	}
	
	$converted_file = $IMAGE_CONVERTED_TABLE{$image_config_id};
	$implement_file = $FILE_PATH_TABLE{$IMAGE_IMPLEMENT_FILE_TABLE{$image_config_id}};
	$header_file = $FILE_PATH_TABLE{$IMAGE_HEADER_FILE_TABLE{$image_config_id}};
	
	#check implement_file
	if(!defined($implement_file) || !($implement_file =~ /(\w+)/))
	{
		return;
	}
	
	#check header file
	#if(!defined($header_file) || !($header_file =~ /(\w+)/))
	#{
	#	return;
	#}
	
	$result = open (HT_CONVERTED_FILE, "<$converted_file");
	
	$result2 = open (HT_IMPLEMENT_FILE, $FILE_FMT_UTF8_APPEND_ENCODING, $implement_file);
	if(defined($header_file))
	{
	    $result3 = open (HT_HEADER_FILE, $FILE_FMT_UTF8_APPEND_ENCODING, $header_file);
	}
	else
	{
	    $result3 = "true";
	}
	
	if(!$result || !$result2 || !$result3)
	{
		close HT_CONVERTED_FILE;
		close HT_IMPLEMENT_FILE;
		if(defined($header_file))
		{
		    close HT_HEADER_FILE;
		}
		return;
	}
	
	$bits_variable = $IMAGE_VARIABLE_NAME_TABLE{$image_config_id} . $IMAGE_CONFIG_VARIABLE_EXT;
	$clut_variable = $IMAGE_VARIABLE_NAME_TABLE{$image_config_id} . $FILE_POSTFIX_CLUT_TABLE{$IMAGE_IMPLEMENT_FILE_TABLE{$image_config_id}};
	$bits_variable_flag = 0;
	$clut_variable_flag = 0;
	$myClutSize			= 0;
	
	while ($line = <HT_CONVERTED_FILE>)
	{
		if($line =~ /(\s*)IMAGE_WIDTH(\s*)=(\s*)(\d+)/)
		{
			$image_width = $4;
			$cur_type = undef;
		}
		elsif($line =~ /(\s*)IMAGE_HEIGHT(\s*)=(\s*)(\d+)/)
		{
			$image_height = $4;
			$cur_type = undef;
		}
		elsif($line =~ /(\s*)IMAGE_PIXEL_BITCOUNT(\s*)=(\s*)(\d+)/)
		{
			$pixel_bitcount = $4;
			$cur_type = undef;
		}
		elsif($line =~ /(\s*)OUTPUT_FORMAT(\s*)=(\s*)(\w+)/)
		{
			$output_format = $4;
			$cur_type = undef;
		}
		elsif($line =~ /(\s*)BITMAP_BITS(\s*)=(\s*)(.*)/)
		{
			$line = $4;
			$cur_type = "found_bits_token";
		}
		elsif($line =~ /(\s*)CLUT_BITS(\s*)=(\s*)(.*)/)
		{
			$line = $4;
			$cur_type = "found_clut_bits_token";
			#print __LINE__ . "[Brian] Find Clut Token \n";
		}
		elsif($line =~ /(\s*)CLUT_SIZE(\s*)=(\s*)(.*)/)
		{
			$myClutSize = $4;
		}
		
		if($cur_type eq "found_clut_bits_token")
		{
			if($line =~ /{(.*)/)
			{
				$line = $1;
				$cur_type = "clut_bits_start";
				#print bits_start prefix, by brian
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_BMP_CLUT_BITS_PREFIX_1;
				print HT_IMPLEMENT_FILE $clut_variable;
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_BMP_CLUT_BITS_PREFIX_2;

				#print bits body
				print HT_IMPLEMENT_FILE $line;
				$clut_variable_flag = 1;
			}
		}
		
		if($cur_type eq "found_bits_token")
		{
			if($line =~ /{(.*)/)
			{
				$line = $1;
				$cur_type = "bits_start";
				
				#print bits_start prefix
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_BMP_BITS_PREFIX_1;
				print HT_IMPLEMENT_FILE $bits_variable;
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_BMP_BITS_PREFIX_2;
				
				#print bits body
				print HT_IMPLEMENT_FILE $line;
				$bits_variable_flag = 1;
			}
		}
		
		if($cur_type eq "bits_start")
		{
			if($line =~ /(.*)}/)
			{
				$line = $1;
				$cur_type = undef;
				
				#print bits body
				print HT_IMPLEMENT_FILE $line;
				
				#print bits_end postfix
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_POSTFIX;
			}
			else
			{
				#print bits body
				print HT_IMPLEMENT_FILE $line;
			}
		}
		
		if($cur_type eq "clut_bits_start")
		{
			if($line =~ /(.*)};/)
			{
				$line = $1;
				$cur_type = undef;
				
				#print bits body
				print HT_IMPLEMENT_FILE $line;
				
				#print bits_end postfix
				print HT_IMPLEMENT_FILE $IMAGE_CONFIG_POSTFIX;
			}
			else
			{
				#print bits body
				print HT_IMPLEMENT_FILE $line;
			}
		}
	}
	
	#output structure for VARIABLE_NAME to .c file
 	# modified by brian, 2006/08/29
 	# if no image, don't output
	if ($bits_variable_flag)
	{
	print HT_IMPLEMENT_FILE $IMAGE_CONFIG_VARIABLE_PREFIX_1;
	print HT_IMPLEMENT_FILE $IMAGE_VARIABLE_NAME_TABLE{$image_config_id};
	print HT_IMPLEMENT_FILE $IMAGE_CONFIG_VARIABLE_PREFIX_2;
	  if ($clut_variable_flag and $bits_variable_flag)
	  {
	  	print HT_IMPLEMENT_FILE "    $image_width, $image_height, $pixel_bitcount, $output_format, $myClutSize, $clut_variable, sizeof($bits_variable), $bits_variable\n";
	  }
	  elsif ($clut_variable_flag and (not $bits_variable_flag))
	  {
	  	# modified by brian, 2006/08/29
	  	# if no image, don't output
	  	#print HT_IMPLEMENT_FILE "    $image_width, $image_height, $pixel_bitcount, $output_format, $myClutSize, $clut_variable, 0, 0\n";
	  	
	  }
	  elsif ((not $clut_variable_flag) and $bits_variable_flag)
	  {
	print HT_IMPLEMENT_FILE "    $image_width, $image_height, $pixel_bitcount, $output_format, 0, 0, sizeof($bits_variable), $bits_variable\n";
	  }
	print HT_IMPLEMENT_FILE $IMAGE_CONFIG_POSTFIX; #postfix for VARIABLE_NAME
	}
	
	#output VARIABLE_NAME to .h file
	if(defined($header_file))
	{
    	print HT_HEADER_FILE $IMAGE_CONFIG_VARIABLE_RPEFIX_3;
    	print HT_HEADER_FILE $IMAGE_VARIABLE_NAME_TABLE{$image_config_id};
    	print HT_HEADER_FILE $IMAGE_CONFIG_POSTFIX_2;
    }
	
	close HT_CONVERTED_FILE;
	close HT_IMPLEMENT_FILE;
	if(defined($header_file))
	{
	    close HT_HEADER_FILE;
	}
}

sub parse_map_table
{
	my ($line);
	my ($line_type);
	my ($result);
	my ($id);
	
	open (H_MAP, "<map.txt");
	
	while ($line = <H_MAP>)
	{
		if(defined($result = is_file_mark($line)))
		{
			$line_type = "file";
			$id = $result;
			next;
		}
		elsif(defined($result = is_section_mark($line)))
		{
			$line_type = "section";
			$id = $result;
			next;
		}
		elsif(defined($result = is_variable_mark($line)))
		{
			$line_type = "variable";
			$id = $result;
			next;
		}
		elsif(defined($result = is_image_mark($line)))
		{
			$line_type = "image";
			$id = $result;
			next;
		}
		
		if($line_type eq "file")
		{
			parse_file_desc($id, $line);
		}
		elsif($line_type eq "section")
		{
			parse_section_desc($id, $line);
		}
		elsif($line_type eq "variable")
		{
			parse_variable_desc($id, $line);
		}
		elsif($line_type eq "image")
		{
			parse_image_desc($id, $line);
		}
	}
	
	close (H_MAP);
}

sub parse_variable_file
{
	my ($variable);
	my ($value);
	my ($append);
	my ($line);
	my ($result);
	my ($statement_end);
	my ($origin);

	open (H_INPUT, "<:raw:encoding(UTF-16LE)", "customized.js");

	while ($line = <H_INPUT>)
	{		
		#remove /**/...should enhance
		if($line =~ m@(.*)/\*(.*)\*/(.*)@)
		{
			$line = $1.$3;
		}
		
		##remove // ...should enhance
		if($line =~ m@(.*)//(.*)@)
		{
			$line = $1;
		}
		
		#split key and value ...should enhance
		if($line =~ /^(\s*)var(\s+)(\w+)(\s*)=(\s*)(.+)/)
		{
			$variable = $3;
			$value = $6;
			
			#append data
			($value, $statement_end) = plus_string($value, undef);
			
			#add setting to value-table
			$VALUE_TABLE{$variable} = $value;
		}
		elsif(defined($variable)) #append string
		{
			$origin = $VALUE_TABLE{$variable};
			
			#append data
			($value, $statement_end) = plus_string($line, $origin);
			
			#add setting to value-table
			$VALUE_TABLE{$variable} = $value;
		}
		else
		{
			$statement_end = "end";
		}
		
		#end a statement
		if(defined($statement_end))
		{
			$variable = undef;
			$value = undef;
			$statement_end = undef;
		}
	}
	
	replace_HTML_specific_tag();
	close(H_INPUT);
}

sub replace_HTML_specific_tag
{
	my ($variable);
	my ($value);
	my ($string);
	
	foreach $variable (keys(%VALUE_TABLE))
	{
		$value = $VALUE_TABLE{$variable};
		
		unless($value =~ /"(.*)"/) #is string
		{
			next;
		}
		else
		{
			$string = $1;
		}
		
		#replace <
		$string =~ s/&lt/</g;
		
		#replace >
		$string =~ s/&gt/>/g;
		
		#replace space
		$string =~ s/&nbsp/ /g;
		
		#replace <BR>
		$string =~ s/<BR>/\\n/g;
		
		$VALUE_TABLE{$variable} = '"' . $string . '"';
	}
}

sub plus_string
{
	my ($value);
	my ($result);
	my ($left);
	my ($middle);
	my ($right);
	my ($statement_end);
	my ($origin);
	my ($is_origin_string);
	$value = $_[0];
	$origin = $_[1];
	
	#check current value
	if(defined($origin))
	{
		if($origin =~ /"(.*)"/) #is string
		{
			$is_origin_string = 1;
		}
		else
		{
			$is_origin_string = 0;
		}
	}
	else
	{
		$is_origin_string = -1;
	}
	
	if(!($value =~ /"(.*)"/))#new value isn't string
	{
		if($is_origin_string == 1)
		{
			$value = $origin; #keep current value
			$statement_end = "end";
		}
		elsif($value =~ /(.*);.*/)#remove ";"
		{
			$value = $origin.$1;
			$statement_end = "end";
		}
		
		return ($value, $statement_end);
	}
	else #new value is string
	{
		if($is_origin_string == 0)
		{
			return ($origin, "end");
		}
	}
	
	$result = $origin;
	do
	{
		if($value =~ /^(\s*)(\+*)(\s*)(")([^"]*)(")(.*)/)
		{
			$left = $4;
			$middle = $5;
			$right = $6;
			$value = $7;
			
			if(defined($result))
			{
				$result =~ /(.+)"/;
				$result = $1.$middle.$right;
			}
			else
			{
				$result .= $4.$5.$6;
			}	
		}
		else
		{
			$value = "";
		}
		
		if($value =~ /[^\s\+]/) #$value includes characters that aren't in [ \r\t\n\f\+]  
		{
			$statement_end = "end";
		}
		
	}while($value);
	
	return ($result, $statement_end);
}
