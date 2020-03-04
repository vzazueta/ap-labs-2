package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	maps := make(map[string]int)
	arr := strings.Fields(s)
	for _, i := range arr {
		maps[i]++
	}
	return maps
}

func main() {
	wc.Test(WordCount)
}

