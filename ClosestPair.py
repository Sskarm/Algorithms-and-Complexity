import math
import matplotlib.pyplot as plt

def distance(p1, p2):
    """Calculates the Euclidean distance between two points.

    Args:
        p1: A 2D point represented as a tuple.
        p2: A 2D point represented as a tuple.

    Returns:
        The Euclidean distance between the two points.
    """

    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def strip_closest(strip, d):
    """Finds the closest pair of points within a given strip.

    Args:
        strip: A list of 2D points within a strip.
        d: The current minimum distance.

    Returns:
        A tuple containing the indices of the closest pair and the minimum distance.
    """

    strip.sort(key=lambda point: point[1])
    min_dist = d
    closest_indices = None

    for i in range(len(strip) - 1):
        for j in range(i + 1, min(i + 12, len(strip))):
            dist = distance(strip[i], strip[j])
            if dist < min_dist:
                min_dist = dist
                closest_indices = (i, j)

    return closest_indices, min_dist

def closest_pair(points):
    """Finds the closest pair of points in a given list.

    Args:
        points: A list of 2D points represented as tuples.

    Returns:
        A tuple containing the closest pair of points and their distance.
    """

    n = len(points)

    if n <= 1:
        return None, float('inf')  # Return None for points and inf for distance

    # Sort points based on x-coordinate
    points.sort(key=lambda point: point[0])

    # Find the middle point
    mid = n // 2
    mid_point = points[mid]

    # Divide points into left and right halves
    left_half = points[:mid]
    right_half = points[mid:]

    # Recursively find the smallest distances in both halves
    left_dist = closest_pair(left_half)
    right_dist = closest_pair(right_half)

    # Find the smaller of the two distances
    d = min(left_dist[1], right_dist[1])

    # Create a strip of points closer than d to the middle line
    strip = [point for point in points if abs(point[0] - mid_point[0]) <= d]

    # Find the closest points in the strip
    closest_indices, strip_dist = strip_closest(strip, d)

    if strip_dist < d:
        closest_pair_points = (strip[closest_indices[0]], strip[closest_indices[1]])
    else:
        closest_pair_points = left_dist if left_dist[1] < right_dist[1] else right_dist

    return closest_pair_points, strip_dist

# Example usage
if __name__ == "__main__":
    points = [(2, 3), (12, 30), (40, 50), (5, 1), (12, 10), (3, 4) , (17,32)]
    closest_points, distance = closest_pair(points)
    print(f"The closest pair of points is: {closest_points}")
    print(f"The distance between them is: {distance}")

    # Visualize the points and the closest pair (access points within closest_points)
    plt.scatter(*closest_points[0], color='red', marker='x', s=100)  # Access first element (point pair)
    plt.scatter(*zip(*points))
    plt.xlabel('X-coordinate')
    plt.ylabel('Y-coordinate')
    plt.title('Closest Pair Visualization')
    plt.show()