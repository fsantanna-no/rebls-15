#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct li {
  int value;
  struct li* rest;
};

struct li* append(struct li* xs, struct li* ys) {
  if (xs) {
    struct li* out = (struct li*) malloc(sizeof(struct li));
    out->value = xs->value;
    out->rest = append(xs->rest, ys);
    return out;
  } else {
    return ys;
  }
}

struct li* rev(struct li* xs, struct li* a) {
  if (xs) {
    struct li* novel = (struct li*) malloc(sizeof(struct li));
    novel->value = xs->value;
    novel->rest = a;
    return rev(xs->rest, novel);
  } else {
    return a;
  }
}

struct li* reverse(struct li* l) {
  return rev(l, NULL);
}

struct lli {
  struct li* value;
  struct lli* rest;
};

struct lli* append_lli(struct lli* xs, struct lli* ys) {
  if (xs) {
    struct lli* out = (struct lli*) malloc(sizeof(struct li));
    out->value = xs->value;
    out->rest = append_lli(xs->rest, ys);
    return out;
  } else {
    return ys;
  }
}

struct lli* rev_lli(struct lli* xs, struct lli* a) {
  if (xs) {
    struct lli* novel = (struct lli*) malloc(sizeof(struct lli));
    novel->value = xs->value;
    novel->rest = a;
    return rev_lli(xs->rest, novel);
  } else {
    return a;
  }
}

struct lli* reverse_lli(struct lli* l) {
  return rev_lli(l, NULL);
}

struct lli* mix(struct li* xs, struct lli* ys) {
  if (xs) {
    struct li* single = (struct li*) malloc(sizeof(struct li));
    single->value = xs->value;
    single->rest = NULL;
    struct lli* novel = (struct lli*) malloc(sizeof(struct lli));
    novel->value = single;
    novel->rest = mix(xs->rest, reverse_lli(ys));
    return append_lli(ys, novel);
  } else {
    return ys;
  }
}

struct lli* mixall(struct lli* xs) {
  if (xs) {
    return mix(xs->value, mixall(xs->rest));
  } else {
    return NULL;
  }
}

int main(int argc, char* argv[]) {
  struct lli* singletons = NULL;
  struct lli* xs;
  int i;
  int tot = 4;
  int* rep = malloc(sizeof(int) * 4);

  for (i = tot-1; i >= 0; i -= 1) {
    struct li* single = (struct li*) malloc(sizeof(struct li));
    single->value = i;
    single->rest = NULL;
    struct lli* novel = (struct lli*) malloc(sizeof(struct lli));
    novel->value = single;
    novel->rest = singletons;
    singletons = novel;
    rep[i] = 0;
  }
  xs = mixall(singletons);
  while (1) {
    // visit
    for (i = 0; i < tot; i += 1) {
      printf("%d, ", rep[i]);
    }
    printf("\n");
    // next
    if (!xs) {
      break;
    }
    assert(xs->value);
    assert(xs->value->rest == NULL);
    rep[xs->value->value] = 1 - rep[xs->value->value];
    xs = xs->rest;
  }
  return 0;
}



