package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

var (
	entering    = make(chan client)
	leaving     = make(chan client)
	messages    = make(chan string) // all incoming client messages
	clients_map = make(map[string]Cliente)
	admin       = "" //clientes[0].username
)

type Cliente struct {
	username string
	conn     net.Conn
	ch       chan string
}

//var clientes []Cliente // all connected clients

func broadcaster() {
	clients := make(map[client]bool)
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}

		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	buffer := make([]byte, 128)
	buffer_len, err := conn.Read(buffer)
	if err != nil {
		log.Fatal(err)
	}

	go clientWriter(conn, ch)
	//fmt.Println(who)

	var who string
	who = string(buffer[:buffer_len])

	c := Cliente{who, conn, ch}

	if admin == "" {
		ch <- "irc-server > Congrats, you were the first user\n"
		ch <- "irc-server > You're the new IRC Server administrator\n"
		fmt.Println("irc-server > [" + who + "] was promoted as the channel administrator\n")
		admin = who
	}

	for _, cli := range clients_map {
		if who == cli.username {
			ch <- "irc-server > Username already taken\n"
			//leaving <- ch
			conn.Close()
			return
		}
	}
	//fmt.Println(who)

	ch <- "irc-server > Welcome to the Simple IRC Server"
	ch <- fmt.Sprintf("irc-server > Your user %s is succesfully logged", who)
	messages <- fmt.Sprintf("irc-server > New connected user %s", who)
	entering <- ch

	input := bufio.NewScanner(conn)

	clients_map[who] = c
	//fmt.Println(c)

	for input.Scan() {
		if input.Text()[0] == '/' {
			subcommand := strings.Fields(input.Text())
			switch subcommand[0] {
			case "/users":
				for cli := range clients_map {
					ch <- cli + ", "
				}
				ch <- string('\n')
			case "/msg":
				other_user := addNewLine(subcommand[1])

				if clientExists(other_user) {
					cli := clients_map[other_user]
					privmessage := who + " [private message] > "
					for i := range subcommand {
						if i > 1 {
							privmessage = privmessage + " " + subcommand[i]
						}
					}
					cli.ch <- privmessage + "\n"

				} else {
					ch <- "The username does not exist\n"
				}

			case "/time":
				ch <- "Local time: " + time.Now().String() + "\n"
			case "/user":
				other_user := addNewLine(subcommand[1])
				if clientExists(other_user) {
					cli := clients_map[other_user]
					ch <- "irc-server > username: " + cli.username + ", IP: " + strings.Split(cli.conn.RemoteAddr().String(), ":")[0] + "\n"
				} else {
					ch <- "The username does not exist\n"
				}

				// WHY DOESN'T IT WOOOOOOORK!!!!????
			case "/kick":
				if admin == who {
					user_to_delete := addNewLine(subcommand[1])
					if clientExists(user_to_delete) {
						messages <- "The user [" + user_to_delete + "] has been kicked\n"

						client := clients_map[user_to_delete]
						client.ch <- "You are kicked from this channel\n"
						client.ch <- "Bad language is not allowed on this channel\n"
						i := client.conn.Close()
						if i != nil {
							log.Println(i)
						}

						//leaving <- client.ch
						delete(clients_map, user_to_delete)
						outMsg := "irc-server > [" + user_to_delete + "] was kicked from channel for bad language policy violation\n"
						messages <- outMsg
						fmt.Println(outMsg)
					} else {
						ch <- "The username does not exist\n"
					}
				} else {
					ch <- "Only administrators can kick out\n"
				}

			default:
				ch <- "Command not valid\n"
			}
		} else if input.Text() == string('\n') {
			messages <- who + ": " + string('\n')
		} else if input.Err() != nil {
			log.Println(input.Err())
		} else {
			messages <- fmt.Sprintf("%s: %s", who, input.Text())
			fmt.Println(who + " > " + input.Text())
		}
	}
	// NOTE: ignoring potential errors from input.Err()

	//fmt.Println("Se salió")

	delete(clients_map, who)
	fmt.Println("[" + who + "] left channel\n")
	if who == admin {
		if len(clients_map) > 0 {
			for i, cli := range clients_map {
				fmt.Println(i)
				admin = i
				cli.ch <- "Now you are the admin\n"
				messages <- "irc-server > [" + i + "] was promoted as the channel administrator\n"
				break
			}
		} else {
			fmt.Println("irc-server > There is not channel administrator\n")
			admin = ""
		}
	}

	leaving <- ch
	conn.Close()
}

func clientExists(target string) bool {
	_, exists := clients_map[target]
	//fmt.Println(exists)
	return exists
}

func addNewLine(oldString string) string {
	return oldString + string('\n')
}

/*
for i, cli := range clients_map {
	fmt.Println(len(i))
}
*/

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {
	host := os.Args[2]
	port := os.Args[4]
	//conn_channel := make(chan net.Conn)

	//clients_map = make(map[string]Cliente)

	listener, err := net.Listen("tcp", host+":"+port)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("irc-server > Simple IRC Server started at %s:%s", host, port)

	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main

