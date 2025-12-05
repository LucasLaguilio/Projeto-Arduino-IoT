const express = require('express')
const server = express()
const port = 8000

server.get('/', (req, res) => {
    res.send("Working!")
    console.log("Working!")
    fetch ('http://192.168.1.100/dados')
    .then(response => {
        if (response.ok) {
            console.log(`esp32 connected, status code: ${response.status}`);
        } else {
            console.log(`esp32, status code: ${response.status}`);
        }
    })
    .catch(error => {
        console.error('Error fetching esp32 status:', error);
    });

})

const cors = require('cors');
server.use(cors({
    origin: '*'
}));

// teste simulando esp
server.get('/dados', async (_req, res) => {
    const a = Math.floor(Math.random() * 100)
    const b = Math.floor(Math.random() * 100);

    const jsondata = {
        sensor1: a,
        sensor2: b
    };
    res.status(200).send(jsondata);
});


server.get('/esp32', async (_req, res) => {
    try {
        const responses = await fetch("http://localhost:8000/dados");
        const datas = await responses.text();
        res.status(200).send(datas);
    } catch (error) {
        res.status(500).send("Something went wrong.")
    }
});

server.listen(port, () => {
    console.log(`Server Running on port ${port} `)
})

