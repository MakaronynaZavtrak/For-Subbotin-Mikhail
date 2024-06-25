void HoareSort(int* arr, int n, int left, int right)
{
	int l = left;
	int r = right;
	int mid = arr[(left + right) / 2];

	while (l <= r)
	{
		while (arr[l] < mid)
			++l;

		while (mid < arr[r])
			--r;

		if (l <= r)
		{
			if (l < r)
				Swap(arr[l], arr[r]);

			++l;
			--r;
		}
	}

	if (left < r)
		HoareSort(arr, n, left, r);

	if (l < right)
		HoareSort(arr, n, l, right);
}
