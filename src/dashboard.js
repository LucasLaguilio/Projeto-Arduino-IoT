const totalVagasText = document.getElementById("total-vagas").innerText;
const vagasOcupadasText = document.getElementById("vagas-ocupadas").innerText;
const vagasLivresText = document.getElementById("vagas-livres").innerText;

const vagasOcupadas = parseInt(vagasOcupadasText);
const vagasLivres = parseInt(vagasLivresText);

const totalVagas = vagasOcupadas + vagasLivres;

document.getElementById("total-vagas").innerText = totalVagas;

const statusdaconexaourl = 'http://localhost:8000/status';
const statusdaconexao = document.getElementById("status-conexao");

async function atualizastatus() {
    try {
        const response = await fetch(statusdaconexaourl);
        if (response.ok) {
            const data = await response.text();
            const splitData = data.split(", status code: 200");
            statusdaconexao.innerText = splitData[0];
        } else {
            statusdaconexao.innerText = `Erro na conexão: ${response.status}`;
        }
    } catch (error) {
        console.error('Error fetching connection status:', error);
        statusdaconexao.innerText = 'Erro ao buscar status de conexão';
    }
}

atualizastatus();
setInterval(atualizastatus, 1000); 