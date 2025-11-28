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
    origin: 'http://192.168.1.100',
    origin: "http://127.0.0.1:5500"
}));



server.get('/esp32', async (_req, res) => {
    try {
        const responses = await fetch("http://192.168.1.100/dados");
        const datas = await responses.json()
        res.status(200).json(datas);
        
        
    } catch (error) {
        if (res.status != 200) {
            res.send("Something went wrong.")
        }
    }
});

server.listen(port, () => {
    console.log(`Server Running on port ${port} `)
})

