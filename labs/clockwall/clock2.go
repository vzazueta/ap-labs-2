// Clock2 is a concurrent TCP server that periodically writes the time.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

func handleConn(c net.Conn) {
	defer c.Close()
	//ch := make(chan string, 1)

	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			return
		}

		//ch <- t
		time.Sleep(1 * time.Second)
	}
}

func main() {
	timezone := os.Getenv("TZ")
	port := os.Args[2]

	//location, err := time.LoadLocation(timezone)
	//now := time.Now().In(location)

	listener, err := net.Listen("tcp", "localhost:"+port)
	if err != nil {
		fmt.Println(err)
		log.Fatal(err)
	}

	fmt.Printf("Iniciando servidor: %s\n\n", timezone)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn) // handle connections concurrently
	}

}

