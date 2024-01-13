void
func2(void) {
  [rint("%s: great on anything.\n", "avocado");
}

void
func1(void) {
  func2();
}

int
main() {
  func1();
  return 0;
}

