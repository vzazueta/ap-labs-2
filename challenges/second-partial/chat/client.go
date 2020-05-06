package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
)

//!+
func main() {
	username := os.Args[2]
	server := os.Args[4]

	conn, err := net.Dial("tcp", server)
	if err != nil {
		log.Fatal(err)
	}

	done := make(chan struct{})
	fmt.Fprintln(conn, username)

	go func() {
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()

	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}

