package main

import (
	"fmt"
	"os"
	"path/filepath"
)

var count [5]int
var leng [6]int
var spaces [6]string

func scanDir(dir string) error {

	err := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
		switch mode := info.Mode(); {
		case mode.IsDir():
			count[0]++
		case mode&os.ModeSymlink != 0:
			count[1]++
		case mode&os.ModeDevice != 0:
			count[2]++
		case mode&os.ModeSocket != 0:
			count[3]++
		default:
			count[4]++
		}

		return nil
	})

	leng[0] = len(dir)

	for i := 1; i < 6; i++ {
		leng[i] = digCount(count[i-1])
	}

	max := Max(leng)
	var hyphens string

	for i := 0; i < max; i++ {
		hyphens += "-"
	}

	for i := 1; i < 6; i++ {
		var sp string
		var spanum int
		spanum = max - leng[i]

		for j := 0; j < spanum; j++ {
			sp += " "
		}

		spaces[i] = sp
	}

	fmt.Printf("+-------------------------+--%s+\n", hyphens)
	fmt.Printf("| Path                    | %s%s |\n", dir, spaces[0])
	fmt.Printf("+-------------------------+--%s+\n", hyphens)
	fmt.Printf("| Directories             | %d%s |\n", count[0], spaces[1])
	fmt.Printf("| Symbolic Links          | %d%s |\n", count[1], spaces[2])
	fmt.Printf("| Devices                 | %d%s |\n", count[2], spaces[3])
	fmt.Printf("| Sockets                 | %d%s |\n", count[3], spaces[4])
	fmt.Printf("| Other files             | %d%s |\n", count[4], spaces[5])
	fmt.Printf("+-------------------------+--%s+\n", hyphens)

	return err
}

func Max(a [6]int) (max int) {
	max = a[0]
	for _, value := range a {
		if value > max {
			max = value
		}
	}
	return max
}

func digCount(number int) int {
	count := 0
	
	if number == 0 {
		return 1
	}	
	
	for number != 0 {
		number /= 10
		count += 1
	}
	return count
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	dir := os.Args[1]
	err := scanDir(dir)

	if err != nil {
		fmt.Printf("Error scanning directory %s: %v", dir, err)
		os.Exit(1)
	}
}
