package main

import (
	"fmt"
	"os"
	"os/signal"
	"time"
)

func main() {

	file, err1 := os.Create("exercise95.txt")
	myErr(err1)
	defer file.Close()

	pp := make(chan int)
	var i int64
	start := time.Now()

	go func() {
		pp <- 1
		for {
			i++
			pp <- <-pp
		}
	}()

	go func() {
		for {
			pp <- <-pp
		}
	}()

	interrupt := make(chan os.Signal, 1)
	signal.Notify(interrupt, os.Interrupt)
	<-interrupt

	fmt.Println()

	_, err2 := file.WriteString(fmt.Sprintf("%v round trips per second", float64(i)/float64(time.Since(start))*1e9))
	myErr(err2)
}

func myErr(err error) {
	if err != nil {
		panic(err)
	}
}

