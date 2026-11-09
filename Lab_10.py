def optimal(pages, capacity):
    frames = []
    faults = 0
    print("\nOptimal Page Replacement:")
    for i, page in enumerate(pages):
        if page not in frames:
            faults += 1
            if len(frames) < capacity:
                frames.append(page)
            else:
                future = pages[i + 1 :]
                next_use = {}
                for frame_page in frames:
                    if frame_page in future:
                        next_use[frame_page] = future.index(frame_page)
                    else:
                        next_use[frame_page] = float("inf")
                victim = max(frames, key=lambda p: next_use[p])
                frames[frames.index(victim)] = page
        print(f"Page {page}: {frames}")
    print("Total Optimal page faults:", faults)
    return faults

if __name__ == "__main__":
    pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]
    capacity = 3
    print("Page Reference String:", pages)
    print("Number of Frames:", capacity)
    optimal(pages, capacity)
