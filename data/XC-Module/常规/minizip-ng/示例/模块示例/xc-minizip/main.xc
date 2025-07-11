函数 整型 test_zip_compat_int(zipFile zip, const char* filename)
	整型 err = ZIP_OK
	zip_fileinfo file_info = { 0 }
	const char* buffer = A"test data"

	file_info.dos_date = mz_zip_time_t_to_dos_date(1588561637)

	err = zipOpenNewFileInZip(zip, filename, &file_info, NULL, 0, NULL, 0, A"test local comment", Z_DEFLATED, 1)

	if(err != ZIP_OK)
		控制台格式输出A(A"Failed to create new file in zip (%d)\n", err)
		return err
	err = zipWriteInFileInZip(zip, buffer, (正整型)strlen(buffer))
	if(err != ZIP_OK)
		控制台格式输出A(A"Failed to write file in zip (%d)\n", err)
		return err
	err = zipCloseFileInZip(zip)
	if(err != ZIP_OK)
		控制台格式输出A(A"Failed to close file in zip (%d)\n", err)
		return err

	return ZIP_OK;

函数 整型 test_zip_compat(void)
	整型 err = ZIP_OK
	zipFile zip = zipOpen(A"compat.zip", APPEND_STATUS_CREATE)
	如果 (zip == NULL)
		控制台格式输出A(A"Failed to create test zip file\n")
		return ZIP_PARAMERROR
	err = test_zip_compat_int(zip, A"test.txt")
	if(err != ZIP_OK)
		return err
	err = test_zip_compat_int(zip, A"test2.txt")
	if(err != ZIP_OK)
		return err

	zipClose(zip, A"test global comment")

	if(err != ZIP_OK)
		return err

	控制台格式输出A(A"Compat zip.. OK\n")
	返回 ZIP_OK

def int test_unzip_compat_int(unzFile unzip)
	unz_global_info64 global_info64{0}
	unz_global_info global_info{0}
	unz_file_info64 file_info64{0}
	unz_file_info file_info{0}
	unz_file_pos file_pos{0}
	int err = UNZ_OK
	int bytes_read = 0
	char comment[120]
	char filename[120]
	char buffer[120]
	const char* test_data = A"test data"

	comment[0] = 0;
	err = unzGetGlobalComment(unzip, comment, sizeof(comment))
	if(err != UNZ_OK)
		控制台格式输出A(A"Failed to get global comment (%d)\n", err)
		return err
	if(strcmp(comment, A"test global comment")!=0)
		控制台格式输出A(A"Unexpected global comment value (%s)\n", comment)
		return err
	err = unzGetGlobalInfo(unzip, &global_info)
	if(err != UNZ_OK)
		控制台格式输出A(A"Failed to get global info  (%d)\n", err)
		return err
	
	err = unzGetGlobalInfo64(unzip, &global_info64)
	if(err != UNZ_OK)
		控制台格式输出A(A"Failed to get global info 64-bit (%d)\n", err)
		return err
	
	if(global_info.number_entry != 2 || global_info64.number_entry != 2)
	
		控制台格式输出A(A"Invalid number of entries in zip (%d)\n", global_info.number_entry)
		return err
	
	if(global_info.number_disk_with_CD != 0 || global_info64.number_disk_with_CD != 0)
		控制台格式输出A(A"Invalid disk with cd (%d)\n", global_info.number_disk_with_CD)
		return err
	
	err = unzLocateFile(unzip, A"test.txt", (unzFileNameComparer)(void *)1)
	if(err != UNZ_OK)
		控制台格式输出A(A"Failed to locate test file (%d)\n", err)
		return err

	err = unzGoToFirstFile(unzip)
	if(err == UNZ_OK)
		filename[0] = 0;
		err = unzGetCurrentFileInfo64(unzip, &file_info64, filename, sizeof(filename), NULL, 0, NULL, 0)
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to get current file info 64-bit (%d)\n", err)
			return err

		err = unzOpenCurrentFile(unzip)
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to open current file (%d)\n", err)
			return err;
		
		bytes_read = unzReadCurrentFile(unzip, buffer, sizeof(buffer))
		if(bytes_read != (int)strlen(test_data))
			控制台格式输出A(A"Failed to read zip entry data (%d)\n", err)
			unzCloseCurrentFile(unzip)
			return err
		
		if(unzEndOfFile(unzip)!=1)
			控制台格式输出A(A"End of unzip not reported correctly\n")
			return UNZ_INTERNALERROR;
		
		err = unzCloseCurrentFile(unzip)
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to close current file (%d)\n", err)
			return err
		
		if(unztell(unzip)!=bytes_read)
			控制台格式输出A(A"Unzip position not reported correctly\n")
			return UNZ_INTERNALERROR;
		
		err = unzGoToNextFile(unzip)
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to get next file info (%d)\n", err)
			return err
		
		comment[0] = 0;
		err = unzGetCurrentFileInfo(unzip, &file_info, filename, sizeof(filename), NULL, 0, comment, sizeof(comment))
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to get current file info (%d)\n", err)
			return err
		
		if(strcmp(comment, A"test local comment")!=0)
			控制台格式输出A(A"Unexpected local comment value (%s)\n", comment)
			return err

		err = unzGetFilePos(unzip, &file_pos)
		if(err != UNZ_OK)
			控制台格式输出A(A"Failed to get file position (%d)\n", err)
			return err
		
		if(file_pos.num_of_file != 1)
			控制台格式输出A(A"Unzip file position not reported correctly\n")
			return UNZ_INTERNALERROR;

		err = unzGetOffset(unzip)
		if(err <= 0)
			控制台格式输出A(A"Unzip invalid offset reported\n")
			return UNZ_INTERNALERROR;

		err = unzGoToNextFile(unzip)

		if(err != UNZ_END_OF_LIST_OF_FILE)
			控制台格式输出A(A"Failed to reach end of zip entries (%d)\n", err)
			unzCloseCurrentFile(unzip)
			return err
		err = unzSeek64(unzip, 0, MZ_SEEK_SET)

	return UNZ_OK

def int test_unzip_compat(void)
	unzFile unzip;
	int err = UNZ_OK;

	unzip = unzOpen(A"compat.zip")
	if(unzip == NULL)
		控制台格式输出A(A"Failed to open test zip file\n")
		return UNZ_PARAMERROR;
	
	err = test_unzip_compat_int(unzip)
	unzClose(unzip)

	if(err != UNZ_OK)
		return err

	控制台格式输出A(A"Compat unzip.. OK\n")

	return UNZ_OK;

函数 整型 入口函数()
	调试输出("控制台程序")
	test_zip_compat()
	test_unzip_compat()
	控制台暂停()
	返回 0
