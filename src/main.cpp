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

bool myOr(bool b1, int i1) {
  return b1 || (1 == i1);
}

bool myAnd(bool b1, int i1) {
  return myOr(b1, i1) && b1;
}

void withNestedCall(int a, bool cond) {
  const int fd = 0;
  unsigned char buffer[512];

  if (15000 == a) {
    // whatever
  }

  // will happen and is raised
  if (cond && myAnd(cond, a)) {
    read(fd, buffer, a);
  }
}

void withAdjacentCalls(int a, bool cond) {
  const int fd = 0;
  unsigned char buffer[512];

  if (15000 == a) {
    // whatever
  }

  // will happen and is raised
  if (cond && myAnd(cond, a) && myOr(cond, a)) {
    read(fd, buffer, a);
  }
}

// copy of the issue:
// https://peach.sonarsource.com/project/issues?id=c-family%3Annn&issues=AXGemnhUwsozUuClDgvO&open=AXGemnhUwsozUuClDgvO

#define PATH_MAX 4096
/* Tokens used for path creation */
#define TOK_SSN 0
#define TOK_MNT 1
#define TOK_PLG 2

#define istopdir(path) ((path)[1] == '\0' && (path)[0] == '/')

static const char *const toks[] = {
    "sessions", "mounts", "plugins", /* must be the last entry */
};
static char *cfgpath;

void *memccpy(void *dest, const void *src, int c, size_t n);

static size_t xstrsncpy(char *dst, const char *src, size_t n) {
  char *end = (char*)memccpy(dst, src, '\0', n);

  if (!end) {
    dst[n - 1] = '\0'; // NOLINT
    end = dst + n; /* If we return n here, binary size increases due to auto-inlining  */
  }
  return end - dst;
}

static size_t mkpath(const char *dir, const char *name, char *out) {
  size_t len;
  /* Handle absolute path */
  if (name[0] == '/') // NOLINT
    return xstrsncpy(out, name, PATH_MAX);
  /* Handle root case */
  if (istopdir(dir))
    len = 1;
  else
    len = xstrsncpy(out, dir, PATH_MAX);
  out[len - 1] = '/'; // NOLINT
  return (xstrsncpy(out + len, name, PATH_MAX - len) + len);
}

static bool load_session(const char *sname, char **path, char **lastdir,
                         char **lastname, bool restore) {
  int i = 0;
  char ssnpath[PATH_MAX];
  char spath[PATH_MAX];

  mkpath(cfgpath, toks[TOK_SSN], ssnpath);
  // ...
  // Whatever
  return true;
}

// Link to the issue:
// https://peach.sonarsource.com/project/issues?id=c-family%3Annn&issues=AXGemnhUwsozUuClDgvP&open=AXGemnhUwsozUuClDgvP

#define NAME_MAX 255
#define CMD_LEN_MAX (PATH_MAX + ((NAME_MAX + 1) << 1))
static const char * const messages[] = {
	"",
	"0 entries",
	"/.nnnXXXXXX",
	"0 selected",
	"cancelled",
	"failed!",
	"session name: ",
	"'c'p / 'm'v as?",
	"'c'urrent / 's'el?",
	"rm -rf %s file%s? [Esc cancels]",
	"limit exceeded",
	"'f'ile / 'd'ir / 's'ym / 'h'ard?",
	"'c'li / 'g'ui?",
	"overwrite?",
	"'s'ave / 'l'oad / 'r'estore?",
	"Quit all contexts?",
	"remote name (- for hovered): ",
	"archive [path/]name: ",
	"open with: ",
	"[path/]name: ",
	"link prefix [@ for none]: ",
	"copy [path/]name: ",
	"\n'Enter' to continue",
	"open failed",
	"dir inaccessible",
	"empty! edit/open with",
	"?",
	"not set",
	"entry exists",
	"too few cols!",
	"'s'shfs / 'r'clone?",
	"refresh if slow",
	"app name: ",
	"'o'pen / e'x'tract / 'l's / 'm'nt?",
	"keys:",
	"invalid regex",
	"'a'u / 'd'u / 'e'xt / 'r'ev / 's'z / 't'm / 'v'er / 'c'lr / '^T'?",
	"unmount failed! try lazy?",
	"first file (\')/char?",
	"remove tmp file?",
	"invalid key",
	"unchanged"
};
#define MSG_KEYS 34

static char g_buf[CMD_LEN_MAX] __attribute__((aligned));

static size_t handle_bookmark(const char *bmark, char *newpath)
{
  int fd;
  size_t r = xstrsncpy(g_buf, messages[MSG_KEYS], CMD_LEN_MAX);
  //...
  // Whatever
  return 0;
}


// copy of the issue:
// https://peach.sonarsource.com/project/issues?id=c-family%3Annn&issues=AXGemnhUwsozUuClDgvQ&open=AXGemnhUwsozUuClDgvQ

typedef unsigned off_t;
typedef unsigned uint_t;

static char *xitoa(uint_t val) {
  static char dst[32] = {'\0'};
  static const char digits[201] = "0001020304050607080910111213141516171819"
                                  "2021222324252627282930313233343536373839"
                                  "4041424344454647484950515253545556575859"
                                  "6061626364656667686970717273747576777879"
                                  "8081828384858687888990919293949596979899";
  uint_t next = 30, quo, i;

  // while (val >= 100) {
  //   quo = val / 100;
  //   i = (val - (quo * 100)) * 2;
  //   val = quo;
  //   dst[next] = digits[i + 1];
  //   dst[--next] = digits[i];
  //   --next;
  // }

  /* Handle last 1-2 digits */
  if (val < 10)
    dst[next] = '0' + val;
  else {
    i = val * 2;
    dst[next] = digits[i + 1];
    dst[--next] = digits[i];
  }

  return &dst[next];
}

static off_t get_size(off_t size, off_t *pval, uint_t comp) {
  off_t rem = *pval;
  off_t quo = rem / 10;

  if ((rem - (quo * 10)) >= 5) {
    rem = quo + 1;
    if (rem == comp) {
      ++size;
      rem = 0;
    }
  } else
    rem = quo;

  *pval = rem;
  return size;
}

size_t strlen(const char *str);

static inline size_t xstrlen(const char * s) {
  return strlen(s); // NOLINT
}

static char *coolsize(off_t size)
{
	const char * const U = "BKMGTPEZY";
	static char size_buf[12]; /* Buffer to hold human readable size */
	off_t rem = 0;
	size_t ret;
	int i = 0;

  // while (size >= 1024) {
	// 	rem = size & (0x3FF); /* 1024 - 1 = 0x3FF */
	// 	size >>= 10;
	// 	++i;
	// }

  if (i == 1) {
		rem = (rem * 1000) >> 10;
		rem /= 10;
		size = get_size(size, &rem, 10);
	} else if (i == 2) {
		rem = (rem * 1000) >> 10;
		size = get_size(size, &rem, 100);
	} else if (i > 2) {
		rem = (rem * 10000) >> 10;
		size = get_size(size, &rem, 1000);
	}

  if (i > 0 && i < 6 && rem) {
		ret = xstrsncpy(size_buf, xitoa(size), 12);
		size_buf[ret - 1] = '.';
		char *frac = xitoa(rem);
		size_t toprint = i > 3 ? 3 : i;
		size_t len = xstrlen(frac);

    if (len < toprint) {
			size_buf[ret] = size_buf[ret + 1] = size_buf[ret + 2] = '0';
			xstrsncpy(size_buf + ret + (toprint - len), frac, len + 1);
		} else
      xstrsncpy(size_buf + ret, frac, toprint + 1);

		ret += toprint;
	} else {
		ret = xstrsncpy(size_buf, size ? xitoa(size) : "0", 12);
		--ret;
	}
	size_buf[ret] = U[i];
	size_buf[ret + 1] = '\0';
	return size_buf;
}
