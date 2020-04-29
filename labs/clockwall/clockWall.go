package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

func clockWall(localh string) {
	//ch := make(chan string, 1)
	timezone := strings.Split(localh, "=")[0]
	port := strings.Split(localh, "=")[1]

	conn, err := net.Dial("tcp", port)
	if err != nil {
		log.Fatal(err)
	}

	done := make(chan int)
	go func() {
		//io.Copy(os.Stdout, conn)
		sc := bufio.NewScanner(conn)

		for sc.Scan() {
			fmt.Println(timezone+"\t"+":", sc.Text())
		}

		log.Println("done")
		done <- 2
	}()

	x := 1
	x = <-done // wait for background goroutine to finish
	log.Println("Channel Closed with value: ", x)
	close(done)
}

func main() {
	args := os.Args[1:]
	c := make(chan int)

	for _, i := range args {
		go clockWall(i)
	}

	<-c
}

