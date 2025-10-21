const totalVagasText = document.getElementById("total-vagas").innerText;
const vagasOcupadasText = document.getElementById("vagas-ocupadas").innerText;
const vagasLivresText = document.getElementById("vagas-livres").innerText;

const vagasOcupadas = parseInt(vagasOcupadasText);
const vagasLivres = parseInt(vagasLivresText);

const totalVagas = vagasOcupadas + vagasLivres;

document.getElementById("total-vagas").innerText = totalVagas;