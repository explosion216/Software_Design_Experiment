import os

# Define the CallRecord class
class CallRecord:
    def __init__(self, caller_area, caller_number, receiver_area, receiver_number, duration):
        self.caller_area = caller_area
        self.caller_number = caller_number
        self.receiver_area = receiver_area
        self.receiver_number = receiver_number
        self.duration = duration  # Duration in seconds

    @staticmethod
    def from_file_line(line):
        parts = line.strip().split()
        return CallRecord(parts[0], parts[1], parts[2], parts[3], int(parts[4]))


# Define the Charge class
class Charge(CallRecord):
    LOCAL_BASE_COST = 0.5
    LOCAL_INCREMENT_COST = 0.2
    LOCAL_INCREMENT_DURATION = 180  # Seconds (3 minutes)
    
    def __init__(self, call_record, rate=0):
        super().__init__(
            call_record.caller_area,
            call_record.caller_number,
            call_record.receiver_area,
            call_record.receiver_number,
            call_record.duration
        )
        self.rate = rate  # Rate per minute for long-distance calls
        self.call_type = "Local" if self.is_local() else "Long-distance"
        self.charge = self.calculate_charge()

    def is_local(self):
        return self.caller_area == self.receiver_area

    def calculate_charge(self):
        if self.is_local():
            if self.duration <= Charge.LOCAL_INCREMENT_DURATION:
                return Charge.LOCAL_BASE_COST
            extra_duration = self.duration - Charge.LOCAL_INCREMENT_DURATION
            increments = extra_duration // Charge.LOCAL_INCREMENT_DURATION
            return Charge.LOCAL_BASE_COST + increments * Charge.LOCAL_INCREMENT_COST
        else:
            minutes = -(-self.duration // 60)  # Ceiling division for partial minutes
            return self.rate * minutes


# Define the User class
class User:
    def __init__(self, number, name):
        self.number = number
        self.name = name

    @staticmethod
    def from_file_line(line):
        parts = line.strip().split()
        return User(parts[0], parts[1])


# Helper function to read call records
def read_call_records(filename):
    call_records = []
    with open(filename, 'r', encoding='utf-8') as file:  # Specify encoding
        for line in file:
            call_records.append(CallRecord.from_file_line(line))
    return call_records


# Helper function to read long-distance rates
def read_long_distance_rates(filename):
    rates = {}
    with open(filename, 'r', encoding='utf-8') as file:  # Specify encoding
        for line in file:
            area, rate = line.strip().split()
            rates[area] = float(rate)
    return rates


# Helper function to read users
def read_users(filename):
    users = {}
    with open(filename, 'r', encoding='utf-8') as file:  # Specify encoding
        for line in file:
            user = User.from_file_line(line)
            users[user.number] = user
    return users



# Calculate charges for each call record
def calculate_charges(call_records, rates):
    charges = []
    for record in call_records:
        rate = rates.get(record.receiver_area, 0)  # Get the rate for long-distance calls
        charge = Charge(record, rate)
        charges.append(charge)
    return charges


# Save calculated charges to a file
def save_charges(filename, charges):
    with open(filename, 'w') as file:
        for charge in charges:
            file.write(f"{charge.caller_number} {charge.call_type} {charge.charge:.2f}\n")


# Query phone bill
def query_phone_bill(phone_number, charges, users):
    user = users.get(phone_number, None)
    if not user:
        print("User not found.")
        return

    local_charge = sum(charge.charge for charge in charges if charge.caller_number == phone_number and charge.call_type == "Local")
    long_distance_charge = sum(charge.charge for charge in charges if charge.caller_number == phone_number and charge.call_type == "Long-distance")
    total_charge = local_charge + long_distance_charge

    print(f"User: {user.name}")
    print(f"Phone Number: {phone_number}")
    print(f"Local Charge: {local_charge:.2f}")
    print(f"Long-Distance Charge: {long_distance_charge:.2f}")
    print(f"Total Charge: {total_charge:.2f}")


# Query call records
def query_call_records(phone_number, call_records, users):
    user = users.get(phone_number, None)
    if not user:
        print("User not found.")
        return

    print(f"Call Records for {user.name} ({phone_number}):")
    for record in call_records:
        if record.caller_number == phone_number:
            print(f"Caller: {record.caller_number}, Receiver: {record.receiver_number}, Duration: {record.duration // 60} minutes")


# Main function to run the system
def main():
    # Updated file paths to point to the B2 subfolder
    call_file = "B2/hd.dat"
    rate_file = "B2/fl.dat"
    user_file = "B2/yh.dat"
    charge_file = "B2/fy.dat"  # Output file for calculated charges
    
    # Load data
    if not (os.path.exists(call_file) and os.path.exists(rate_file) and os.path.exists(user_file)):
        print("One or more input files are missing in the B2 directory.")
        return
    
    call_records = read_call_records(call_file)
    rates = read_long_distance_rates(rate_file)
    users = read_users(user_file)
    
    # Calculate and save charges
    charges = calculate_charges(call_records, rates)
    save_charges(charge_file, charges)

    # Query options
    phone_number = input("Enter phone number to query bill or call records: ")
    query_type = input("Choose query type (1: Phone Bill, 2: Call Records): ")
    
    if query_type == "1":
        query_phone_bill(phone_number, charges, users)
    elif query_type == "2":
        query_call_records(phone_number, call_records, users)
    else:
        print("Invalid query type.")

if __name__ == "__main__":
    main()
