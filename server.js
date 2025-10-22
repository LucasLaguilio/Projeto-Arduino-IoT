const express = require('express')
const server = express()
const port = 8000

server.get('/', (req, res) => {
    res.send("Working!")
    console.log("Working!")
    fetch ('http://localhost:5000/arduino')
    .then(response => {
        if (response.ok) {
            console.log(`Arduino connected, status code: ${response.status}`);
        } else {
            console.log(`Arduino Not Found, status code: ${response.status}`);
        }
    })
    .catch(error => {
        console.error('Error fetching Arduino status:', error);
    });

})

const cors = require('cors');
server.use(cors({
    origin: 'http://localhost:5500', 
    origin: 'http://localhost:5000/arduino'
}));



server.get('/status', (_req, res) => {
    try {
        if (res.status(200)) {
            setTimeout(() => {
                res.send(`Conectado, status code: ${res.statusCode}`);
                // console.log(`Server is up and running, status code: ${res.statusCode}`);
            }, 1000);
        } else {
            res.status(404).send(`Not Found, status code: ${res.statusCode}`);
            console.log(`Not Found, status code: ${res.statusCode}`);   
        }
    } catch (err) {
        res.status(500).send(`Server error, status code: ${res.statusCode}`);
        console.log(`Server error, status code: ${res.statusCode}`, err);
    }
});

server.listen(port, () => {
    console.log(`Server Running on port ${port} `)
})

