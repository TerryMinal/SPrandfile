#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int randint(){
  int fd = open("/dev/random", O_RDONLY);
  int buffer;
  read(fd, &buffer, sizeof(int));
  if (errno) {
    printf("%s", strerror(errno));
  }
  close(fd);
  return buffer;
}

int main(){

  printf("\nGenerating Random Numbers:\n");
  int rand_nums[10];
  int i;
  int random;
  //fills the array of rand_nums with random numbers generated from randint()
  for(i = 0; i < 10; i++){
    random = randint();
    printf("\tRandom %d: %d\n", i, random);
    rand_nums[i] = random;
  }
  printf("\nWriting numbers To file new_random...\n");
  int fd;
  //O_CREAT | O_WRONLY create a new file if there doesn't exist one. Opens new_random with write only if it exists
  //if the file doesnt exist, then create it with permissions 0644 (rw-r--r--)
  fd = open("new_random", O_CREAT|O_WRONLY, 0644);
  //writes to the files the rand_nums
  write(fd, rand_nums, sizeof(rand_nums));
  if (errno) {
    printf("%s", strerror(errno));
  }
  close(fd);
  printf("...Done writing\n");
  // reading file into a different array
  printf("Reading rand_nums into a different array...\n");
  int new_rand = open("new_random", O_RDONLY);
  int new_arr[10];
  int num_read = read(new_rand, &new_arr, sizeof(rand_nums));
  if (errno) {
    printf("%s", strerror(errno));
  }
  for (i = 0; i < 10; i++) {
    printf("random number read from file rand_num: %d\n", new_arr + i);
  }
  printf("...done with reading rand_nums\n");

}
