

int ClampSymmetricValue(int value,int limit)

{
  if (value > limit) {
    return limit;
  }
  if (value < -limit) {
    value = -limit;
  }
  return value;
}
