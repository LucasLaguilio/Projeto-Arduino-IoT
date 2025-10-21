const express = require('express')
const server = express()
const port = 8000

server.get('/', (req, res) => {
    res.send("Working!")
    console.log("Working!")
})

server.get('/status', (req, res) => {

})


server.listen(8000, () => {
    console.log(`Server Running on port ${port} `)
})

