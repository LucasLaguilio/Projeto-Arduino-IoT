const totalVagasText = document.getElementById("total-vagas").innerText;
const vagasOcupadasText = document.getElementById("vagas-ocupadas").innerText;
const vagasLivresText = document.getElementById("vagas-livres").innerText;
const valortext = document.getElementById("valor");


const vagasOcupadas = parseInt(vagasOcupadasText);
const vagasLivres = parseInt(vagasLivresText);

const totalVagas = vagasOcupadas + vagasLivres;

document.getElementById("total-vagas").innerText = totalVagas;

const urlsensor = "http://localhost:8000/esp32";

const statusdaconexaourl = 'http://localhost:8000/status';
const statusdaconexao = document.getElementById("status-conexao");

async function atualizastatus() {
    try {
        const response = await fetch(urlsensor);
            const data = await response.json(); 
            valortext.innerText = data.valor;
    } catch (error) {
        console.error('Error fetching connection status:', error);
        statusdaconexao.innerText = 'Erro ao buscar status de conexão';
    }
}

atualizastatus();
setInterval(atualizastatus, 1000); 