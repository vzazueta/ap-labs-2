package main

import (
	"flag"
	"fmt"
	"log"
	"os"

	"github.com/adonovan/gopl.io/ch5/links"
)

//!+sema
// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var (
	tokens = make(chan struct{}, 20)
	seen   = make(map[string]bool)
)

func crawl(url string) []string {
	fmt.Println(url)
	tokens <- struct{}{} // acquire a token
	list, err := links.Extract(url)
	<-tokens // release the token

	if err != nil {
		log.Print(err)
	}
	return list
}

func crawlRec(depth int, url string, finish chan bool) {
	if depth == 0 {
		finish <- true
		return
	}

	visited, confirm := seen[url]
	if visited && confirm {
		finish <- true
		return
	} else {
		seen[url] = true
	}

	urls := crawl(url)

	urlsFinished := make(chan bool)
	for _, link := range urls {
		go crawlRec(depth-1, link, urlsFinished)
		<-urlsFinished
	}

	finish <- true
}

func main() {

	if len(os.Args) != 3 {
		fmt.Println("Incorrect Format")
		return
	}

	depth := flag.Int("depth", 1, "crawl until limit depth")
	flag.Parse()

	url := os.Args[2]
	seen[url] = false

	done := make(chan bool)
	go crawlRec(*depth, url, done)
	<-done
}

