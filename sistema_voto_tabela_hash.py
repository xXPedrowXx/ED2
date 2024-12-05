# Dicionário para armazenar os IDs dos eleitores que já votaram
voter_hash_table = {}

# Dicionário para armazenar os votos dos candidatos
vote_count = {}

def vote(voter_id, candidate):

    if voter_id in voter_hash_table:
        return "Erro: Eleitor já votou."
    else:
        voter_hash_table[voter_id] = True  # Marca o eleitor como já tendo votado
        vote_count[candidate] = vote_count.get(candidate, 0) + 1  # Incrementa o voto do candidato
        return f"Voto registrado para {candidate}!"

def show_results():

    if not vote_count:
        return "Nenhum voto registrado."
    
    results = "Resultado da eleição:\n"
    for candidate, votes in vote_count.items():
        results += f"{candidate}: {votes} votos\n"
    return results.strip()

# Exemplo de uso
print(vote("123", "Alice"))  # Voto registrado
print(vote("123", "Bob"))    # Erro: Já votou
print(vote("456", "Bob"))    # Voto registrado
print(vote("789", "Alice"))  # Voto registrado
print(show_results())        # Resultados
