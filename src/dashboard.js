const vagasOcupadasText = document.getElementById("vagas-ocupadas").innerText;
const vagasLivresText = document.getElementById("vagas-livres").innerText;
const valortext = document.getElementById("valor");
const valortext2 = document.getElementById("valor2");
const vagasOcupadas = parseInt(vagasOcupadasText);
const vagasLivres = parseInt(vagasLivresText);




const urlsensor = "http://localhost:8000/esp32";

const statusdaconexaourl = 'http://localhost:8000/status';
const statusdaconexao = document.getElementById("status-conexao");



async function atualizasensor() {
    try {
        const response = await fetch(urlsensor);
        const data = await response.json();
        const datasensor1 = data.sensor1; 
        const datasensor2 = data.sensor2;


        let ocupadas = 0;
        if (datasensor1 < 50) ocupadas++;
        if (datasensor2 < 50) ocupadas++;

        let livres = 0;
        if (datasensor1 >= 50) livres++;
        if (datasensor2 >= 50) livres++;

        document.getElementById("vagas-ocupadas").innerText = ocupadas;
        document.getElementById("vagas-livres").innerText = livres;

        valortext.innerText = datasensor1;
        valortext2.innerText = datasensor2;
    } catch (error) {
        console.error('Error fetching connection ', error);
        statusdaconexao.innerText = 'Erro ao buscar conexão';
    }
}






atualizasensor();
setInterval(atualizasensor, 1000); 