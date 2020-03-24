package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Path []Point

type Point struct {
	x, y float64
}

func Distance(p, q Point) float64 {
	return math.Hypot(q.x-p.x, q.y-p.y)
}

func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.x-p.x, q.y-p.y)
}

func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

func main() {
	var sides int
	rand.Seed(time.Now().UnixNano())
	sides, _ = strconv.Atoi(os.Args[1])
	path := make(Path, sides)
	distances := make([]float64, sides)

	for i := 0; i < sides; i++ {
		var p Point = Point{(rand.Float64()*(100-(-100)) + (-100)), (rand.Float64()*(100-(-100)) + (-100))}

		if i > 3 {
			for j := 0; (j + 1) < (i - 1); j++ {
				//println(j)
				if doIntersect(path[j], path[j+1], path[i-1], p) == true {
					p = Point{(rand.Float64()*(100-(-100)) + (-100)), (rand.Float64()*(100-(-100)) + (-100))}
					j = 0
				}
			}
		}

		path[i] = p

	}

	for i := 0; i < sides-1; i++ {
		distances[i] = Distance(path[i], path[i+1])
	}

	distances[sides-1] = Distance(path[sides-1], path[0])

	var res float64 = path.Distance()

	fmt.Printf("- Generating a [%d] sides figure\n", sides)
	fmt.Println("- Figure's vertices ")

	for i := 0; i < sides; i++ {
		fmt.Printf("- (%f, %f)\n", path[i].x, path[i].y)
	}

	fmt.Println("- Figure's Perimeter")
	fmt.Printf("- %f ", distances[0])

	for i := 1; i < sides; i++ {
		fmt.Printf("+ %f ", distances[i])
	}

	fmt.Printf("= %f\n\n", res)
}

func onSegment(p, q, r Point) bool {
	if q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y) {
		return true
	}

	return false
}

func max(x, y float64) float64 {
	if x < y {
		return y
	}
	return x
}

func min(x, y float64) float64 {
	if x > y {
		return y
	}
	return x
}

func orientation(p, q, r Point) int {
	var val float64 = ((q.y-p.y)*(r.x-q.x) - (q.x-p.x)*(r.y-q.y))

	if val == 0 {
		return 0
	} else if val == 1 {
		return 1
	}

	return 2
}

func doIntersect(p1, q1, p2, q2 Point) bool {
	var o1 int = orientation(p1, q1, p2)
	var o2 int = orientation(p1, q1, q2)
	var o3 int = orientation(p2, q2, p1)
	var o4 int = orientation(p2, q2, q1)

	if o1 != o2 && o3 != o4 {
		return true
	}

	if o1 == 0 && onSegment(p1, p2, q1) {
		return true
	}

	if o2 == 0 && onSegment(p1, q2, q1) {
		return true
	}
	if o3 == 0 && onSegment(p2, p1, q2) {
		return true
	}
	if o4 == 0 && onSegment(p2, q1, q2) {
		return true
	}

	return false
}
