n_arr = np.logspace(1, 4, 4, dtype=np.int32)

def game():
    door = [1, 2, 3]
    prize_door = np.random.randint(1, len(door)+1, dtype='int')
    chosen_door = np.random.randint(1, len(door)+1, dtype='int')
    if prize_door == chosen_door:   # Monty chooses randomly to open one of the 2 possible doors
        p = np.where(door == prize_door, 0, 0.5)
        opened_door = np.random.choice(door, p=p)
    else:   # Monty only has 1 possible door to open
        p = np.where(np.logical_or(door == prize_door, door == chosen_door), 0, 1)
        opened_door = np.random.choice(door, p=p)
    door.remove(opened_door)   # This is when the remaining 2/3 condenses 
    second_door = np.random.choice(door)   # Assuming that the contestant chooses randomly still
    switch = True
    win = 0
    if second_door == chosen_door: 
        switch = False
    if second_door == prize_door: 
        win = 1
    return switch, win

for n in n_arr:
    print("N =", n)
    switch_arr = np.empty((0))
    stay_arr = np.empty((0))
    for i in range(n):
        switch, win = game()
        if switch == True: 
            switch_arr = np.append(switch_arr, win)
        else: 
            stay_arr = np.append(stay_arr, win)
    switch_win_prob = switch_arr.sum() / len(switch_arr)   # win is either 0 or 1, so taking the sum works
    stay_win_prob = stay_arr.sum() / len(stay_arr)         # len() is how many times switching (or not) was done
    print("P(Prize if Switch) =", switch_win_prob)
    print("P(Prize if no Switch) =", stay_win_prob)
    print("Ratio Switch/noSwitch =", switch_win_prob/stay_win_prob)   # should tend to 2 in long run, (2/3)/(1/3) = 2
    print()
