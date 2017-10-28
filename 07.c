#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int randint(){
  int fd = open("/dev/random", O_RDONLY, sizeof(int));
  int buffer;
  read(fd, &buffer, sizeof(int));
  close(fd);
  return buffer;
}

int main(){

  printf("\nGenerating Random Numbers:\n");
  int rand_nums[10];
  int i;
  for(i = 0; i < 10; i++){
    int random = randint();
    printf("\tRandom %d: %d\n", i, random);
    rand_nums[i] = random;
  }

  printf("\nWriting Numbers To File...\n");
  int fd;
  fd = open("file", O_CREAT|O_WRONLY, 0644);
  write(fd, rand_nums, sizeof(rand_nums));
  close(fd);


}
