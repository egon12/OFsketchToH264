#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include "../src/image/JpgSaver.hpp"


int main(int argc, char* argv[]) {

  if (argc != 4) {
    std::cout << "Argument must 3 got " << argc;
    return -1;
  }

  int width = atoi(argv[2]);
  int height = atoi(argv[3]);
  char* filesource_name = argv[1];


  struct stat stat_buf;
  int err = stat(filesource_name, &stat_buf);
  if (err < 0) {
    printf("Cannot get size of \"%s\"", filesource_name);
    return err;
  }
  int filesource_size = stat_buf.st_size;

  unsigned char *data = (unsigned char*) malloc(filesource_size);

  FILE *filesource = fopen(filesource_name, "rb");

  int result = fread(data, 1, filesource_size, filesource);
  if (result != filesource_size) {
    std::cout << "must read " << filesource_size << " but only able to read " << result;
    return -1;
  }
  std::cout << "read " << result << " data " << "\n";


  JpgSaver *saver = new JpgSaver();
  const char * fileresult_name = "/tmp/result.jpg";
  std::cout << "saving to file!!!\n";
  saver->save((char *) fileresult_name, data, width, height);
  delete saver;

  return 0;
}
