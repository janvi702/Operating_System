def fifo(pages, capacity):
frames = []
pointer = 0
faults = 0
print("\nFIFO Page Replacement:")
for page in pages:
if page not in frames:
faults += 1
if len(frames) < capacity:
frames.append(page)
else:
frames[pointer] = page
pointer = (pointer + 1) % capacity
print(f"Page {page}: {frames}")
print("Total FIFO page faults:", faults)
return faults
def lru(pages, capacity):
frames = []
last_used = {}
faults = 0
print("\nLRU Page Replacement:")
for time, page in enumerate(pages):
if page not in frames:
faults += 1
if len(frames) < capacity:
frames.append(page)
else:
least_recent = min(frames, key=lambda p: last_used[p])
frames[frames.index(least_recent)] = page
last_used[page] = time
print(f"Page {page}: {frames}")
print("Total LRU page faults:", faults)
return faults
if __name__ == "__main__":
pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]
capacity = 3
print("Page Reference String:", pages)
print("Number of Frames:", capacity)
fifo(pages, capacity)
lru(pages, capacity)