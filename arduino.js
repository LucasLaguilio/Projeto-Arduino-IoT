const express = require('express')
const server = express()
const port = 5000

server.get('/', (req, res) => {
    res.send("Arduino Server is Running!")
    console.log("Arduino Server is Running!")
})

server.get('/arduino', (req, res) => {
    if (res.status(200)) {
        res.send(`Arduino connected, status code: ${res.statusCode}`);
        console.log(`Arduino connected, status code: ${res.statusCode}`);
    } else {
        res.status(404).send(`Arduino Not Found, status code: ${res.statusCode}`);
        console.log(`Arduino Not Found, status code: ${res.statusCode}`);   
    }
})

server.post('/arduino', (req, res) => {
    if (res.status(200)) {
        res.send(`Arduino connected, status code: ${res.statusCode}`);
        console.log(`Arduino connected, status code: ${res.statusCode}`);
    } else {
        res.status(404).send(`Arduino Not Found, status code: ${res.statusCode}`);
        console.log(`Arduino Not Found, status code: ${res.statusCode}`);   
    }
})

server.listen(port, () => {
    console.log(`Arduino Server Running on port ${port}`)
})
