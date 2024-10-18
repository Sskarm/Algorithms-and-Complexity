import matplotlib.pyplot as plt

def convex_hull_trivial(points):
    """
    Computes the convex hull of a set of points in trivial case (<= 3 points).

    Args:
        points: A list of 2D points.

    Returns:
        A list of points representing the convex hull in counterclockwise order.
    """

    if len(points) <= 1:
        return points
    elif len(points) == 2:
        return [points[0], points[1]]
    else:
        # Sort points by y-coordinate
        points.sort(key=lambda p: p[1])
        return [points[0], points[1], points[2]]

def ccw(p1, p2, p3):
    """
    Determines if three points are counterclockwise.

    Args:
        p1: The first point.
        p2: The second point.
        p3: The third point.

    Returns:
        True if the points are counterclockwise, False otherwise.
    """

    return (p2[1] - p1[1]) * (p3[0] - p2[0]) - (p2[0] - p1[0]) * (p3[1] - p2[1]) > 0

def convex_hull_divide_and_conquer(points):
    if len(points) <= 3:
        return convex_hull_trivial(points)

    # Sort points by x-coordinate
    points.sort(key=lambda p: p[0])

    # Divide the points into two halves
    mid = len(points) // 2
    left_hull = convex_hull_divide_and_conquer(points[:mid])
    right_hull = convex_hull_divide_and_conquer(points[mid:])

    # Find the upper and lower tangent points
    upper_left, upper_right = find_tangent(left_hull, right_hull, True)
    lower_left, lower_right = find_tangent(left_hull, right_hull, False)

    # Merge the hulls
    merged_hull = []
    i = left_hull.index(upper_left)
    while True:
        merged_hull.append(left_hull[i])
        if left_hull[i] == lower_left:
            break
        i = (i + 1) % len(left_hull)

    i = right_hull.index(lower_right)
    while True:
        merged_hull.append(right_hull[i])
        if right_hull[i] == upper_right:
            break
        i = (i + 1) % len(right_hull)

    return merged_hull


def find_tangent(left_hull, right_hull, upper):
    left_index = max(range(len(left_hull)), key=lambda i: left_hull[i][0])
    right_index = min(range(len(right_hull)), key=lambda i: right_hull[i][0])

    while True:
        changed = False
        if upper:
            while ccw(right_hull[right_index], left_hull[left_index], left_hull[(left_index + 1) % len(left_hull)]) > 0:
                left_index = (left_index + 1) % len(left_hull)
                changed = True
            while ccw(left_hull[left_index], right_hull[right_index], right_hull[(right_index - 1) % len(right_hull)]) < 0:
                right_index = (right_index - 1) % len(right_hull)
                changed = True
        else:
            while ccw(right_hull[right_index], left_hull[left_index], left_hull[(left_index - 1) % len(left_hull)]) < 0:
                left_index = (left_index - 1) % len(left_hull)
                changed = True
            while ccw(left_hull[left_index], right_hull[right_index], right_hull[(right_index + 1) % len(right_hull)]) > 0:
                right_index = (right_index + 1) % len(right_hull)
                changed = True
        if not changed:
            break

    return left_hull[left_index], right_hull[right_index]


def visualize_convex_hull(points, hull):
    """
    Visualizes the convex hull and the original points.

    Args:
        points: A list of 2D points.
        hull: A list of points representing the convex hull.
    """

    plt.figure(figsize=(8, 6))
    plt.scatter([p[0] for p in points], [p[1] for p in points], label="Points")
    plt.plot([p[0] for p in hull], [p[1] for p in hull], label="Convex Hull")
    plt.title("Convex Hull Visualization")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.legend()
    plt.show()

# Test case
points = [(0, 0), (1, 1), (2, 0), (0, 2), (2, 2), (1, 3), (-1, 0), (-2, 1)]
hull = convex_hull_divide_and_conquer(points)
print("Convex Hull:", hull)
visualize_convex_hull(points, hull)