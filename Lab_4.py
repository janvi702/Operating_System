import multiprocessing
import time
import random

def access_resource(process_id, semaphore):
    """
    Simulates a worker process attempting to access a limited shared resource.
    """
    print(f"[Process {process_id}] is waiting to access the resource...")
    
    # Acquire the semaphore (decrements the internal counter)
    # If the counter is 0, the process blocks/waits until another process releases it
    semaphore.acquire()
    
    try:
        print(f"👉 [Process {process_id}] HAS ACCESSED the resource.")
        
        # Simulate processing time inside the critical section
        duration = random.uniform(1.5, 2.5)
        time.sleep(duration)
        
    finally:
        print(f"✅ [Process {process_id}] is releasing the resource and leaving.")
        # Release the semaphore (increments the internal counter)
        semaphore.release()

if __name__ == '__main__':
    # Initialize a Semaphore that allows a maximum of 2 processes at the same time
    max_connections = 2
    resource_semaphore = multiprocessing.Semaphore(max_connections)
    
    # Create a list to track 5 target worker processes
    processes = []
    
    print(f"--- Starting Simulation (Max allowed concurrent processes: {max_connections}) ---\n")
    
    # Spawn 5 distinct processes
    for i in range(1, 6):
        p = multiprocessing.Process(target=access_resource, args=(i, resource_semaphore))
        processes.append(p)
        p.start()
        # Slight delay in spawning to make console logs easier to track
        time.sleep(0.2)
        
    # Wait for all processes to complete execution
    for p in processes:
        p.join()
        
    print("\n--- Simulation Complete. All processes have finished safely. ---")
