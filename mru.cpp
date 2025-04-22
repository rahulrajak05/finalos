#include <stdio.h>

int main() {
  int n, frames[10], pages[15], page_faults = 0;
  int i, j, k, flag, mru[10], max, pos;

  printf("Enter the number of frames: ");
  scanf("%d", &n);

  printf("Enter the reference string: ");
  for (i = 0; i < 15; i++) {
  scanf("%d", &pages[i]);
  }

  for (i = 0; i < n; i++) {
  frames[i] = -1;
  mru[i] = 0;
  }

  for (i = 0; i < 15; i++) {
  flag = 0;
  for (j = 0; j < n; j++) {
  if (frames[j] == pages[i]) {
  flag = 1;
  mru[j] = i + 1;
  break;
  }
  }

  if (flag == 0) {
  pos = 0;
  max = mru[0];
  for (k = 1; k < n; k++) {
  if (mru[k] > max) {
  max = mru[k];
  pos = k;
  }
  }
  frames[pos] = pages[i];
  mru[pos] = i + 1;
  page_faults++;
  }

  printf("\nPage %d: ", pages[i]);
  for (j = 0; j < n; j++) {
  printf("%d ", frames[j]);
  }
  }

  printf("\n\nTotal number of page faults: %d\n", page_faults);

  return 0;
}