require "json"

N     = 10
ITERS = 15

struct Point
  getter x, y

  def initialize(@x : Float64, @y : Float64)
  end

  def +(p : Point)
    Point.new @x + p.x, @y + p.y
  end

  def -(p : Point)
    Point.new @x - p.x, @y - p.y
  end

  def /(d)
    Point.new @x / d, @y / d
  end

  def modulus
    Math.sqrt(sq(@x) + sq(@y))
  end
end

def sq(d : Float64)
  d * d
end

def dist(x : Point, y : Point)
  (x - y).modulus
end

def average(xs : Array(Point))
  xs.reduce { |x, y| x + y } / xs.size
end

def closest(x : Point, choices : Array(Point))
  choices.min_by { |y| dist(x, y) }
end

def clusters(xs : Array(Point), centroids : Array(Point))
  xs.group_by { |x| closest(x, centroids) }.values
end

def run(xs : Array(Point))
  centroids = xs.first(N)

  ITERS.times do
    centroids = clusters(xs, centroids).map { |l| average(l) }
  end

  centroids
end

str = File.read("../points.json")

xs = Array(Point).new
Array(Array(Float64)).from_json(str) do |elem|
  xs << Point.new elem.at(0), elem.at(1)
end

BM_ITERATIONS = 100

before = Time.now
BM_ITERATIONS.times do
  centroids = run(xs)
  # puts "centroids: \n #{centroids}"
end
after = Time.now

time = ((after - before) / BM_ITERATIONS).milliseconds

puts "Made #{BM_ITERATIONS} iterations with an average of #{time} milliseconds"
