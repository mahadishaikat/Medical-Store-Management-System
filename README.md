# 🏥 Medical Store Management System

**A C-based console application for efficiently managing a medical store's inventory and user operations.**

## 📋 Features

- **User Roles**: Admins and regular users with unique permissions.
- **Inventory Management**: Add, update, display, search, and delete medicine records.
- **Cart & Checkout**: Add items to cart and manage purchases.
- **Data Persistence**: Save/load medicine data to/from a file.

## 📂 Project Structure

- **Medicine Management**: 
  - Add new medicines to the inventory.
  - Update details of existing medicines.
  - Search for specific medicines by name.
  - Delete medicines from the stock.

- **User Management**: 
  - Register and log in with user roles.
  - Admins have access to full inventory controls.
  - Regular users can browse and add medicines to the cart.

- **Data Handling**:
  - Save and load the medicine inventory to/from a text file (`medicine_data.txt`) for persistence.

## 📈 Use Case Diagram
<img src="https://raw.githubusercontent.com/mahadishaikat/Medical-Store-Management-System/refs/heads/main/images/Use%20Case%20Diagram.jpg" alt="**Add Alternative Texts for Image Tab** - A guide to enhance accessibility by including descriptive alt texts." width="600" />

## ⚙️ Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/mahadishaikat/Medical-Store-Management-System
   cd MedicalStoreManagementSystem

2. Compile the code:
   ```bash
   gcc medical_store.c -o medical_store

3. Run the application:
   ```bash
   ./medical_store

## 🚀 Usage

- **Admin** can:
  - Add, update, delete, search medicines.
  - Save and load inventory data.

- **Regular Users** can:
  - Search and view medicines.
  - Add medicines to the cart and checkout.

## 🔑 Key Code Highlights

- **Inventory Limit**: Maximum of 100 medicines.
- **User Limit**: Up to 10 users can register.
- **File Operations**: Data is stored in `medicine_data.txt` file for loading and saving inventory data.

## 🤖 Example Operations

### Admin Menu
- Add new medicine: `AddMedicine()`
- Display all medicines: `DisplayMedicines()`
- Update medicine info: `UpdateMedicine()`
- Save/load inventory: `SaveData()` / `LoadData()`

### User Menu
- Login/register: `LoginUser()` / `RegisterUser()`
- Add to cart: `AddToCart()`
- Checkout: `CheckoutCart()`

## 📜 License
  Read [Full Documentation](./LICENSE) From Here.
  ```bash
  This project is for educational purposes and is licensed under the MIT License.
