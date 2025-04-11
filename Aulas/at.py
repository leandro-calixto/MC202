###################################################
# MC102 - Algoritmos e Programação de Computadores
# Laboratório 4 - Batalha Pokémon
# Nome: Ana Beatriz Rodrigues Carvalho
# RA: 238029
###################################################
'''
Um pokémon A enfrenta um pokémon B, e cada pokémon tem um valor de pontos de vida (hp, do inglês Health Points). A cada turno cada pokémon lança um ataque, sendo que o primeiro ataque é realizado pelo pokémon mais rápido, e cada ataque diminui os pontos de vida do pokémon sendo atacado. A batalha continua até que um dos pokémon não tenha mais pontos de vida.
Cada ataque tem um valor x, que indica a força do ataque, e um multiplicador y, que indica se o ataque foi efetivo (y=2), normal (y=1), ou não efetivo (y=0.5). Um ataque diminui em x*y unidades o hp do pokémon adversário. Os valores de ataque são sempre pares, o que garante que x*y é um número inteiro.
Ao final de cada turno, você deverá imprimir o hp de cada pokémon.
Lembre-se que o ataque do pokémon com maior velocidade é considerado primeiro ao diminuir o hp do oponente. O hp de cada pokémon nunca será negativo, sendo que seu valor mínimo é zero. No momento que o hp de um dos pokémon chega em zero o mesmo é considerado como derrotado e a batalha é considerada encerrada, mesmo que isso ocorra no meio de um turno. Ao final da batalha, após imprimir o hp de cada pokémon, seu programa deve imprimir o nome e o hp do pokémon que venceu a batalha:
'''

# Leitura dos valores iniciais
hp_ivysaur = int(input())                          #vida do ivysaur
hp_pikachu = int(input())                          #vida do pikachu
velocidade_ivysaur = int(input())                  #velocidade do ivysaur
velocidade_pikachu = int(input())                  #velocidade do pikachu

# ataques dos turnos
while hp_ivysaur > 0 and hp_pikachu > 0:
    x1 = int(input())                              #força do golpe do oponente mais rápido
    y1 = float(input())                            #efetividade do golpe do oponente mais rápido
    x2 = int(input())                              #força do golpe do oponente mais lerdo
    y2 = float(input())                            #efetividade do golpe do oponente mais lerdo
    if velocidade_ivysaur > velocidade_pikachu:
        hpjb = x1*y1                               #golpe do ivysaur    
        hpja = x2*y2                               #golpe do pikachu
        hp_pikachu = hp_pikachu - hpjb             #atualização da vida do pikachu
        if hp_pikachu <= 0:
            hp_pikachu = 0                              #pikachu perdeu
            print('HP Ivysaur = ', int(hp_ivysaur))
            print('HP Pikachu = ', int(hp_pikachu))
        else:
            hp_ivysaur = hp_ivysaur - hpja              #atualização da vida do ivysaur
            if hp_ivysaur <= 0:                    
                hp_ivysaur = 0                          #ivysaur perdeu
            print('HP Ivysaur = ', int(hp_ivysaur))
            print('HP Pikachu = ', int(hp_pikachu))

    else:
        hpja = x1*y1                              #golpe do pikachu
        hpjb = x2*y2                              #golpe do ivysaur 
        hp_ivysaur = hp_ivysaur - hpja            #atualização da vida do ivysaur
        if hp_ivysaur <= 0:
            hp_ivysaur = 0                        #ivysaur perdeu
            print('HP Ivysaur = ', int(hp_ivysaur))
            print('HP Pikachu = ', int(hp_pikachu))
    
        else:
            hp_pikachu = hp_pikachu - hpjb        #ayualização da vida do ivysaur
            if hp_pikachu <0:
               hp_pikachu = 0                     #ivysaur perdeu
            print('HP Ivysaur = ', int(hp_ivysaur))
            print('HP Pikachu = ', int(hp_pikachu))

# Determina o vencedor
if hp_ivysaur == 0:
    print('Pokémon Vencedor: Pikachu\nHP do Vencedor:', int(hp_pikachu))
else:
    print('Pokémon Vencedor: Ivysaur\nHP do Vencedor:', int(hp_ivysaur))