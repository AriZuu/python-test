class Test:
  def __init__(self):
    self.val = 1

  def add(self, val):
    self.val = self.val + val
    print("Value now", self.val)
