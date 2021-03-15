package main

import "github.com/gofiber/fiber"

func main() {
	app := fiber.New()

	app.Static("/", "../components/")

	app.Listen(":4000")
}
