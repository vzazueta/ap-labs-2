package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	ady := make([][]uint8, dy)
	adx := make([]uint8, dx)
	
	for x := range ady {
	 for y := range adx {
   	  adx[y] = uint8((x+y)/2)
	    }
	 ady[x] = adx
	 }

	return ady
}

func main() {
	pic.Show(Pic)
}

