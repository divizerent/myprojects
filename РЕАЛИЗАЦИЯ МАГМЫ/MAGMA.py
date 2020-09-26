#!/usr/bin/env python3 
import random
from sys import argv 

def main():
    mas = [0]*64
    RMas = LMas = [0]*32

    print("ENTER MODE")
    print("1 -> ENCRYPTION")
    print("2 -> DECRYPTION")
    mode = input()
#шифрование
    if mode == '1':
        data  = open(argv[1], 'rb')
        data1 = data.read()

        #data  = open('dolgosrok_3.py', 'rb').read()
        #data  = open('spirit.png', 'rb').read()
        num2 = data1.hex()
        block_text = str(num2)
        data.close()#считываем файл бинарно и закрываем его
        alph = ['1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f']

        str_block_text = str(block_text)
        print("1 -> YOUR KEY")
        print("2 -> GENERATION KEY")
        print("3 -> TEST")
        while 1:
            flag = input()
            if flag=='1':
                print("Enter your Key len 64. Mas symbols[1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f]")
                while 1:
                    key = input()
                    if len(key)==64:
                        break
                    print("non 64")
                break
            if flag=='2':
                key = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"#гостовский ключ
                KEY = ['0']*len(key)
                for i in range(len(key)):
                    KEY[i] = random.choice(alph)
                key = ''.join(KEY)#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                print("random key is -> ",key)
                break

            if flag=='3':   
                key = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"#гостовский ключ
                break
        #print(KEY)

        len_str_block_text = len(str_block_text)
        BUFF_OPEN = ""
        BUFF_CLOSE = ""
    

        random_sin = random.randint(0,99999999) #случайное число для вектора
        rand_str = str(random_sin)
        random_num_str = '0'*(8 -len(rand_str)) +rand_str + '0'*8
        #print(random_num_str)
        gamma_buff = text_buff = gamma = text = random_num_str # это вектор!!!!
        
        fl = open(argv[1], 'w')
        fl.write(random_num_str)
        fl.close()

        micro_block = [0]*16
        micro_block1 = [0]*16
        buff_encr =""
        buff_incr =""
        mod = len_str_block_text % 16
        if mod!=0: # дополнение открытого текста до кратной длины
            mod  = 16 -mod
            str_block_text = "0"*mod +str_block_text
        len_text1 = len(str_block_text)
        mod  = len_text1 // 16
        block = 16
        for i in range(mod):
            for j in range(16):
                micro_block[j] = str_block_text[j+block*i]

            micro_block_str = ''.join(micro_block)
            txt = ''.join(text_buff)
            LMas = txt[0:8]
            RMas = txt[8:16]
            #print(len(micro_block_str))
            #key = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"#гостовский ключ


            LMas, RMas = encryption(LMas, RMas, key)

            txt1 = LMas + RMas
            buff_encr = txt1
            BE = int(buff_encr, 16)
            T = int(micro_block_str, 16)
            XOR_EN_BE = [0]*64
            XOR_EN_T = [0]*64
            be_bin = bin(BE)[2:]
            t_bin = bin(T)[2:]
            str_be_num = '0'*(64-len(be_bin))+be_bin

            str_t_num = '0'*(64-len(t_bin))+t_bin

            XOR_EN_T = [int(j) for j in str_t_num]
            XOR_EN_BE = [int(j) for j in str_be_num]
            for x in range(64):
                XOR_EN_T[x] = XOR_EN_T[x] ^ XOR_EN_BE[x]# xor гаммы и блока открытого текста 


            text_buff_int = int(text_buff)
            text_buff_int = text_buff_int + 1
            text_buff = str(text_buff_int)

            T = int(''.join([str(f) for f in XOR_EN_T]),2)
            text = str(hex(T))
            text = text[2:]
            text = '0'*(16- len(text)) + text
            BUFF_CLOSE = BUFF_CLOSE + text

        print("Длина закрытого текста",len(BUFF_CLOSE)/16)
        fl1 = open(argv[1], "ab")
        b_BUFF = str(hex(int(BUFF_CLOSE, 16)))
        b_BUFF = bytearray.fromhex(b_BUFF[2:])
        fl1.write(b_BUFF)# результат круга "шифрование-расшифрование" можно увидеть в файле 
        fl1.close()

#Расшифрование 

    if mode=='2':
        fl = open(argv[1], 'rb')
        mas_gamma_start = fl.read(16)
        print(mas_gamma_start)
        mas_gamma_start = str(int(mas_gamma_start))
        print(mas_gamma_start)
        mas_block_close = fl.read()
        num1= mas_block_close.hex()
        mas_block_close = str(num1)
        mas_block_close = str(mas_block_close)
        fl.close()
        print("Enter key")
        while 1:
            print("IF TEST-> PRESS 0")
            key = input()
            if key=='0':
                key = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
            if len(key)==64:
                break
            print("non 64")


        len_str_block_text = len(mas_block_close)
        str_block_text = mas_block_close
        BUFF_OPEN = ""
        BUFF_CLOSE = ""
        gamma_buff = text_buff = gamma = text = mas_gamma_start # это вектор
        micro_block = [0]*16
        micro_block1 = [0]*16
        buff_encr =""
        buff_incr =""
        mod = len_str_block_text % 16
        if mod!=0: # дополнение открытого текста до кратной длины
            mod  = 16 -mod
            str_block_text = "0"*mod +mas_block_close
        len_text1 = len(str_block_text)
        mod  = len_text1 // 16
        block = 16

        print("Длина закрытого текста",len(str_block_text)/16)





        for i in range(mod):
            for j in range(16):
                #print(j)
                #print(j+block*i)
                micro_block1[j] = str_block_text[j+block*i]

            micro_block1_str = ''.join(micro_block1)
            txt = ''.join(gamma_buff)
            LMas = txt[0:8]
            RMas = txt[8:16]
            #key = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"

            LMas, RMas = encryption(LMas, RMas, key)

            txt1 = LMas + RMas
            txt2 = LMas + RMas

            buff_incr = txt2
            BI = int(buff_incr, 16) 
            T = int(micro_block1_str,16)
            XOR_EN_BI = [0]*64
            XOR_EN_T = [0]*64
            bi_bin = bin(BI)[2:]
            t_bin = bin(T)[2:]
            str_bi_num = '0'*(64-len(bi_bin))+bi_bin
    
            str_t_num = '0'*(64-len(t_bin))+t_bin
    
            XOR_EN_T = [int(j) for j in str_t_num]
            XOR_EN_BI = [int(j) for j in str_bi_num]
            for x in range(64):
                XOR_EN_T[x] = XOR_EN_T[x] ^ XOR_EN_BI[x]
            gamma_buff_int = int(gamma_buff)
            gamma_buff_int = gamma_buff_int + 1
            gamma_buff = str(gamma_buff_int)

            T = int(''.join([str(f) for f in XOR_EN_T]),2)
            text1 = str(hex(T))
            text1 = text1[2:]
            text1 = '0'*(16 - len(text1)) + text1

            BUFF_OPEN = BUFF_OPEN + text1


        print("Длина конечного текста",len(BUFF_OPEN)/16)
        fl = open(argv[1], "wb")
        b_BUFF = str(hex(int(BUFF_OPEN, 16)))
        b_BUFF = bytearray.fromhex(b_BUFF[2:])
        fl.write(b_BUFF)# результат круга "шифрование-расшифрование" можно увидеть в файле 
        fl.close()







def encryption(LMas, RMas, key):
    summ = 0
    summ1 = 0
    key_str = ['a']*8
    ii = 0



    box  = [[12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1],
        [6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15],
        [11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0],
        [12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11],
        [7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12],
        [5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0],
        [8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7],
        [1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2]]

    for q in range(0,64,8):#деление ключа на итерационные ключи
        key_str[ii] = key[q:q+8]
        ii+=1
    for y in range(32):
        if summ==8:
            summ=0
        if y>23:
            K = int(key_str[7-summ], 16)
        else:
            K = int(key_str[summ], 16)
        summ += 1
        R = int(RMas,16)
        L = int(LMas, 16)
        RMas1 = [0]*32
        buff_num = bin(R)[2:]
        str_buff_num = '0'*(32-len(buff_num))+buff_num
        RMas1 = [int(j) for j in str_buff_num]
        buff = RMas1[:]

        lmas_num = bin(L)[2:]
        str_lmas_num = '0'*(32-len(lmas_num))+lmas_num
        LMas = [int(j) for j in str_lmas_num]

        R = (K+R) & 0xffffffff #арифметическое сложение 
        rmas_num = bin(R)[2:]
        str_rmas_num = '0'*(32-len(rmas_num))+rmas_num
        RMas = [int(j) for j in str_rmas_num]

        l=0
        for i in range(32, 0, -4): #работа с таблицей подстановок 
            k = int(''.join([str(f) for f in RMas[i-4:i]]),2)
            num = box[l][k]
            bin_num = bin(num)[2:]
            str_bin_num = '0'*(4-len(bin_num))+bin_num
            RMas[i-4:i] = [int(j) for j in str_bin_num]
            l+=1
        steps = 11 # Количество позиций для сдвига
        RMas = RMas[steps:] + RMas[:steps]

        for i_3 in range(32):
            RMas[i_3] =  RMas[i_3] ^ LMas[i_3] #xor левой и правой части 
        for i in range(32):
            LMas[i] = buff[i]

        L = int(''.join([str(f) for f in LMas]),2)
        R = int(''.join([str(f) for f in RMas]),2)

        LMas = str(hex(L))
        RMas = str(hex(R))
        RMas = RMas[2:]
        LMas = LMas[2:]

        ll = len(LMas)
        lr = len(RMas)
        if ll<8:
            delta = 8 -ll
            LMas = '0'*delta + LMas
        if lr<8:
            delta = 8 -lr
            RMas = '0'*delta + RMas

    return LMas, RMas



if __name__ == "__main__":
    main()







