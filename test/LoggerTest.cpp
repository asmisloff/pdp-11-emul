#include "../Logger.h"

void test() {
    Logger logger;
    const char *fmt = "%d + %d = %d\n";
    int a = 2;
    int b = 3;
    logger.setLevel(INFO);
    logger.debug(fmt, a, b, a + b);
    logger.setLevel(ERROR);
    logger.info(fmt, a, b, a + b);
    logger.error(fmt, a, b, a + b);
}

int main() {
    test();
    return 0;
}