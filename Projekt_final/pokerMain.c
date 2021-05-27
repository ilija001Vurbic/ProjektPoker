#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "karte.h"

int main() {
    spil.brojPodKarata = 0;
    srand(time(NULL));
    generiranjeRuke();
    ispisiRuke();
    usporediRuke();
    return 0;
}