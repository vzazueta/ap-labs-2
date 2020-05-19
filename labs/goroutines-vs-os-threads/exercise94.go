package main

import (
	"flag"
	"fmt"
	"os"
	"runtime"
	"time"
)

var idle = make(chan struct{})

func myErr(err error) {
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func pipeline(in chan struct{}, out chan struct{}, current int, total *int) {
	if current != *total {
		go pipeline(out, in, current+1, total)
		out <- <-in
	} else {
		idle <- struct{}{}
	}
}

func main() {
	pipes := flag.Int("pipes", 30000000, "total number of pipes")
	flag.Parse()

	file, err := os.Create("exercise94.txt")
	myErr(err)

	defer file.Close()

	_, err1 := file.WriteString("Before:\n" + memoryReport())
	myErr(err1)
	in := make(chan struct{})
	out := make(chan struct{})
	go pipeline(in, out, 0, pipes)

	start := time.Now()
	in <- struct{}{}
	<-idle

	_, err2 := file.WriteString("After:\n" + memoryReport())
	myErr(err2)
	_, err3 := file.WriteString(fmt.Sprintf("Total pipes: %d\nIn total time: %s\n", *pipes, time.Since(start)))
	myErr(err3)
}

func memoryReport() string {
	var memory runtime.MemStats
	runtime.ReadMemStats(&memory)

	return fmt.Sprintf("\tAlloc = %v MiB\n\tMallocs = %v\n\tFrees = %v\n\tCurrent Mallocs = %v\n\tHeapAlloc = %v MiB\n\tSys = %v MiB\n\tInUse = %v\n", bytesToMegabytes(memory.Alloc), memory.Mallocs, memory.Frees, memory.Mallocs-memory.Frees, bytesToMegabytes(memory.HeapAlloc), bytesToMegabytes(memory.Sys), bytesToMegabytes(memory.HeapInuse))
}

func bytesToMegabytes(x uint64) uint64 {
	return (x / 1024 / 1024)
}

