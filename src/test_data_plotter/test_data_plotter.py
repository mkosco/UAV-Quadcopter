import matplotlib.pyplot as plt
from datetime import datetime
import matplotlib.dates as mdates

file = open('test_data/testrun_29.10.2023_1%_Steps_4s_hold.txt', 'r')

# Lists to store the time and value data
times = []
values = []

try:
    for line in file:
        # Split each line into time and value
        parts = line.strip().split(', ')
        if len(parts) == 2:
            timestamp_str, value_str = parts
            # Convert the timestamp to a datetime object
            timestamp = datetime.strptime(timestamp_str, "%Y-%m-%d %H:%M:%S.%f")
            # Convert the value to a float
            grams = abs(float(value_str))
            newton = (grams / 1000.0) * 9.78
            times.append(timestamp)
            values.append(newton)

    # Create Plot
    plt.figure(figsize=(10, 6))
    plt.gca().xaxis.set_major_formatter(mdates.DateFormatter("%Y-%m-%d %H:%M:%S"))
    plt.gca().xaxis.set_major_locator(mdates.DayLocator(interval=1))
    plt.plot(times, values, linestyle='-', color='b')  # Use linestyle='-'
    plt.xlabel('Time')
    plt.ylabel('Newton')
    plt.title('Lift')
    plt.xticks(rotation=45)
    plt.grid()

    # Show the plot
    plt.tight_layout()
    plt.show()

except FileNotFoundError:
    print(f"File not found")
except Exception as e:
    print(f"An error occurred: {e}")
