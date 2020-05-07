trials=1000000
trial = sample(1:3, trials, replace=T)
player = sample(1:3, trials, replace=T)
host=vector(length = trials)

for (i in 1:trials) 
{

    if(trial[i]==player[i])
    {
    
        leftOver=setdiff(c(1,2,3), trial[i])
    
    }
    else
    {
    
        leftOver=setdiff(c(1,2,3), c(trial[i], player[i]))
    
    }

    host[i] = leftOver[sample(1:length(leftOver),1)]

}

stayingChance= which(trial==player)
changingVec=vector(length = trials)

for (i in 1:trials) 
{

    changeIndexes = setdiff(c(1,2,3), c(host[i], player[i]))
    changingVec[i] = changeIndexes[1]
    
}

changingChance = which(trial==changingVec)


sprintf("Kiserletek szama: %i", trials)
length(stayingChance)
length(changingChance)
length(stayingChance)/length(changingChance)
length(stayingChance)+length(changingChance)
