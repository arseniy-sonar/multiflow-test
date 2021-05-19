typedef unsigned long long size_t;
typedef int ssize_t;

ssize_t read(int fildes, void* buf, size_t nbyte);
// CHECK -1:26 -1:35 S945:Do not pass an array as a single pointer. Consider using std::span or reference to an array to avoid array to pointer decay.

bool alwaysTrue() { return true; }
// CHECK -1:21 -1:27 S3400:Remove this function and declare a constant for this value.

void read0Returns0(int a, bool cond) {
  const int fd = 0;
  unsigned char buffer[512];

  int b = 502;
  int c = 1000;
  bool cond2 = cond;

  if (10 == a) {
    //nothing
  }

  if (11 == a) {
    return;
  }
  if (cond2) {

    if (cond) {
      b = 19;
      b = c + 1;
    }

    // will happen and is raised
    if (alwaysTrue()) {
      read(fd, buffer, a + b);
    }
  }

}
