import unittest


class Node:
    def __init__(self, L, R):
        self.nxt = None
        self.L = L
        self.R = R


def has_node_overlap(node_x, node_y):
    if node_x == None or node_y == None:
        return True
    if node_x.R < node_y.L:
        return False
    if node_x.L > node_y.R:
        return False
    return True


def get_merged_node(node_x, node_y):
    if node_x == None:
        return node_y
    if node_y == None:
        return node_x
    L = min(node_x.L, node_y.L)
    R = max(node_x.R, node_y.R)
    return Node(L, R)


def get_merge_lists(list_x, list_y):
    current_x = list_x
    current_y = list_y

    merged_list = []
    current_merged_node = None

    while current_x != None or current_y != None:
        to_add = None
        if current_x != None and current_y != None:
            if has_node_overlap(current_x, current_y):
                to_add = get_merged_node(current_x, current_y)
                current_x = current_x.nxt
                current_y = current_y.nxt
            elif current_x.L < current_y.L:
                to_add = current_x
                current_x = current_x.nxt
            else:
                to_add = current_y
                current_y = current_y.nxt
        elif current_x != None:
            to_add = current_x
            current_x = current_x.nxt
        else:
            to_add = current_y
            current_y = current_y.nxt
        if has_node_overlap(current_merged_node, to_add):
            current_merged_node = get_merged_node(current_merged_node, to_add)
        else:
            merged_list.append(current_merged_node)
            current_merged_node = to_add

    if to_add != None:
        merged_list.append(current_merged_node)

    return merged_list


class Test(unittest.TestCase):
    def testWithSampleCase1(self):
        list_x = Node(1, 2)
        list_x.nxt = Node(3, 4)
        list_x.nxt.nxt = Node(5, 6)

        list_y = Node(2, 3)
        list_y.nxt = Node(4, 5)
        list_y.nxt.nxt = Node(6, 7)

        merged_lists = get_merge_lists(list_x, list_y)
        for i in merged_lists:
            print(i.L, i.R)
        print()

    def testWithSampleCase2(self):
        list_x = Node(1, 2)
        list_x.nxt = Node(3, 4)
        list_x.nxt.nxt = Node(5, 6)

        list_y = Node(2, 3)

        merged_lists = get_merge_lists(list_x, list_y)
        for i in merged_lists:
            print(i.L, i.R)
        print()

    def testWithSampleCase3(self):
        list_x = Node(1, 4)
        list_x.nxt = Node(7, 8)

        list_y = Node(1, 3)
        list_y.nxt = Node(6, 9)

        merged_lists = get_merge_lists(list_x, list_y)
        for i in merged_lists:
            print(i.L, i.R)
        print()

    def testWithSampleCase4(self):
        list_x = Node(1, 1)
        list_x.nxt = Node(2, 2)

        list_y = Node(3, 3)
        list_y.nxt = Node(4, 4)

        merged_lists = get_merge_lists(list_x, list_y)
        for i in merged_lists:
            print(i.L, i.R)
        print()


if __name__ == '__main__':
    unittest.main()
