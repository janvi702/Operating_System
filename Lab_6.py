def first_fit(blocks, processes): 
    allocation = [-1] * len(processes) 
    temp = blocks.copy() 
    
    for i in range(len(processes)): 
        for j in range(len(temp)): 
            if temp[j] >= processes[i]: 
                allocation[i] = j 
                temp[j] -= processes[i] 
                break 
                
    print("\n--- First Fit ---") 
    print(f"{'Process':<10}{'Size':<10}{'Block':<10}") 
    print("-" * 30)
    for i in range(len(processes)): 
        if allocation[i] != -1: 
            print(f"P{i + 1:<9}{processes[i]:<10}B{allocation[i] + 1}") 
        else: 
            print(f"P{i + 1:<9}{processes[i]:<10}Not Allocated") 


def best_fit(blocks, processes): 
    allocation = [-1] * len(processes) 
    temp = blocks.copy() 
    
    for i in range(len(processes)): 
        best = -1 
        for j in range(len(temp)): 
            if temp[j] >= processes[i]: 
                if best == -1 or temp[j] < temp[best]: 
                    best = j 
                    
        if best != -1: 
            allocation[i] = best 
            temp[best] -= processes[i] 
            
    print("\n--- Best Fit ---") 
    print(f"{'Process':<10}{'Size':<10}{'Block':<10}") 
    print("-" * 30)
    for i in range(len(processes)): 
        if allocation[i] != -1: 
            print(f"P{i + 1:<9}{processes[i]:<10}B{allocation[i] + 1}") 
        else: 
            print(f"P{i + 1:<9}{processes[i]:<10}Not Allocated") 


def worst_fit(blocks, processes): 
    allocation = [-1] * len(processes) 
    temp = blocks.copy() 
    
    for i in range(len(processes)): 
        worst = -1 
        for j in range(len(temp)): 
            if temp[j] >= processes[i]: 
                if worst == -1 or temp[j] > temp[worst]: 
                    worst = j 
                    
        if worst != -1: 
            allocation[i] = worst 
            temp[worst] -= processes[i] 
            
    print("\n--- Worst Fit ---") 
    print(f"{'Process':<10}{'Size':<10}{'Block':<10}") 
    print("-" * 30)
    for i in range(len(processes)): 
        if allocation[i] != -1: 
            print(f"P{i + 1:<9}{processes[i]:<10}B{allocation[i] + 1}") 
        else: 
            print(f"P{i + 1:<9}{processes[i]:<10}Not Allocated") 


def main(): 
    print("===== MEMORY ALLOCATION =====") 
    m = int(input("Enter number of memory blocks: ")) 
    blocks = [] 
    
    print("\nEnter memory block sizes:") 
    for i in range(m): 
        size = int(input(f"Block {i + 1}: ")) 
        blocks.append(size) 
        
    n = int(input("\nEnter number of processes: ")) 
    processes = [] 
    
    print("\nEnter memory required by each process:") 
    for i in range(n): 
        size = int(input(f"Process {i + 1}: ")) 
        processes.append(size) 
        
    while True: 
        print("\n========== MENU ==========") 
        print("1. First Fit") 
        print("2. Best Fit") 
        print("3. Worst Fit") 
        print("4. Exit") 
        
        choice = int(input("Enter your choice: ")) 
        if choice == 1: 
            first_fit(blocks, processes) 
        elif choice == 2: 
            best_fit(blocks, processes) 
        elif choice == 3: 
            worst_fit(blocks, processes) 
        elif choice == 4: 
            print("Program terminated.") 
            break 
        else: 
            print("Invalid choice!") 


if __name__ == "__main__": 
    main()
