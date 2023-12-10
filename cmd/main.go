package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	// Define command-line flags
	name := flag.String("name", "", "Your name")
	age := flag.Int("age", 0, "Your age")
	isStudent := flag.Bool("student", false, "Are you a student?")

	// Parse the command-line arguments
	flag.Parse()

	// Check if the name flag is provided
	if *name != "" {
		fmt.Printf("Hello, %s!\n", *name)
	}

	// Check if the age flag is provided
	if *age != 0 {
		fmt.Printf("You are %d years old.\n", *age)
	}

	// Check the student flag
	if *isStudent {
		fmt.Println("You are a student.")
	}

	// If no flags are provided, print usage
	if flag.NFlag() == 0 {
		fmt.Println("Usage: mycliapp [OPTIONS]")
		flag.PrintDefaults()
		os.Exit(1)
	}
}
