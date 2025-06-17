# Projeto de Linhas de Ônibus em Grafos

Utilizando informações disponibilizadas pela URBS acerca da frota ônibus de Curitiba e seus trajetos, este projeto visa encontrar o menor caminho entre duas paradas de ônibus informadas pelo usuário através de um algoritmo de busca em largura.

### Implementações futuras
- Validação dos dados inseridos
- Validação de limites
- Implementar pesos
- Usar stderr nas saídas de erro
- Mostrar os nomes das paradas de ônubus + nomes do ônibus

### Observações
- O programa (ainda) **não conta com medidas de peso**, portanto o caminho gerado não visa a economia de passagens e nem economia de tempo de trajeto, somente leva em consideração a menor distância em termos de conexão entre paradas.
- O arquivo _.json_ com as informações das paradas de ônibus pode ser encontrado [aqui](https://dadosabertos.curitiba.pr.gov.br/conjuntodado/detalhe?chave=ca40f13b-ef61-472b-810f-dd705f85fd2e).