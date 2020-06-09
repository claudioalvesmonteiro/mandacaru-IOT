# -*- coding: utf-8 -*-

from google.colab import drive
drive.mount('/content/drive')

#### Importar pacotes

# import packages
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import cv2
import random
import pickle 
import tensorflow as tf

## Pré-processamento

def importarPlantas(caminho, classificacao):
  ''' funcao importarPlantas
      caminho: caminho ate a pasta das imagens
      classificacao: acesso a subpasta 'doentes' ou 'saudaveis'
  '''
  # ler imagens na pasta
  imagens = os.listdir(caminho+classificacao)
  # loop para importar e preprocessar imagens
  caracteristicas=[]
  for imagem in imagens:
    img_array = cv2.imread(caminho+classificacao+'/'+imagem, cv2.IMREAD_GRAYSCALE) # ler arquivo em escala de cinza
    img_array = cv2.resize(img_array, (100,150), interpolation = cv2.INTER_AREA) # reduzir tamanho da imagem
    img_array = tf.keras.utils.normalize(img_array, axis=1) # normalizar array
    img_array = img_array.reshape(-1)        
    caracteristicas.append(img_array)
  # criar lista do alvo
  if classificacao == 'doentes':
    alvo = [1]*len(caracteristicas)
  elif classificacao == 'saudaveis':
    alvo = [0]*len(caracteristicas)
  # retornar valores
  return alvo, caracteristicas

# importar imagens
caminho = '/content/drive/My Drive/Projetos/Proj-Extensao-Programacao-IA-2020/Apresentacoes/Material-Aulas/Aula-3-Classificacao-RNA--Claudio-Estela-Gustavo/imagens_plantas/manga/'
doentes_alvo, doentes = importarPlantas(caminho, 'doentes')

saudaveis_alvo, saudaveis = importarPlantas(caminho, 'saudaveis')

# combinar doentes e saudaveis
import numpy as np
alvo =  np.asarray(doentes_alvo + saudaveis_alvo)
caracteristicas =  np.asarray(doentes + saudaveis)

# dividir em teste e treinamento
from sklearn.model_selection import train_test_split
caracteristicas_treino, caracteristicas_teste, alvo_treino, alvo_test = train_test_split(caracteristicas, alvo, test_size=0.2, random_state=89)

caracteristicas.shape

# Construção da Rede Neural

#### Camadas

import keras

model = keras.models.Sequential()
model.add(keras.layers.core.Dense(512, input_shape=tuple([caracteristicas.shape[1]]), activation='relu'))
model.add(keras.layers.core.Dense(360, activation='relu'))
model.add(keras.layers.core.Dense(360, activation='relu'))
model.add(keras.layers.core.Dense(64, activation='relu'))
model.add(keras.layers.core.Dense(2,   activation='softmax'))
model.compile(loss="sparse_categorical_crossentropy", optimizer="adam",metrics=["accuracy"])

print(model.summary())

#### Treinar/Testar o modelo

# train
model.fit(caracteristicas_treino, alvo_treino, epochs=30)

## avaliar
val_loss, val_acc = model.evaluate(caracteristicas_teste, alvo_test)

print(val_loss, val_acc)