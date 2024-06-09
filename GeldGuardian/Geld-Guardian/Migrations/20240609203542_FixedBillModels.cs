using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Geld_Guardian.Migrations
{
    /// <inheritdoc />
    public partial class FixedBillModels : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills");

            migrationBuilder.AlterColumn<int>(
                name: "StatusId",
                table: "bills",
                type: "INTEGER",
                nullable: false,
                defaultValue: 1,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldNullable: true);

            migrationBuilder.AlterColumn<int>(
                name: "PaymentMethodId",
                table: "bills",
                type: "INTEGER",
                nullable: false,
                defaultValue: 1,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldNullable: true);

            migrationBuilder.AlterColumn<int>(
                name: "CategoryId",
                table: "bills",
                type: "INTEGER",
                nullable: false,
                defaultValue: 8,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldNullable: true);

            migrationBuilder.AlterColumn<int>(
                name: "CategoryId",
                table: "BillItems",
                type: "INTEGER",
                nullable: false,
                defaultValue: 8,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldNullable: true);

            migrationBuilder.InsertData(
                table: "Categorie",
                columns: new[] { "CategorieId", "Description", "Name" },
                values: new object[,]
                {
                    { 1, null, "Groceries" },
                    { 2, null, "Utilities" },
                    { 3, null, "Rent" },
                    { 4, null, "Transportation" },
                    { 5, null, "Health" },
                    { 6, null, "Entertainment" },
                    { 7, null, "Education" },
                    { 8, null, "Other" }
                });

            migrationBuilder.InsertData(
                table: "PaymentMethod",
                columns: new[] { "PaymentId", "Description", "Name" },
                values: new object[,]
                {
                    { 1, null, "Cash" },
                    { 2, null, "Credit Card" },
                    { 3, null, "Debit Card" },
                    { 4, null, "Bank Transfer" },
                    { 5, null, "PayPal" },
                    { 6, null, "Other" }
                });

            migrationBuilder.InsertData(
                table: "PaymentStatus",
                columns: new[] { "StatusId", "Name" },
                values: new object[,]
                {
                    { 1, "Pending" },
                    { 2, "Paid" },
                    { 3, "Overdue" }
                });

            migrationBuilder.AddForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills",
                column: "PaymentMethodId",
                principalTable: "PaymentMethod",
                principalColumn: "PaymentId",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills",
                column: "StatusId",
                principalTable: "PaymentStatus",
                principalColumn: "StatusId",
                onDelete: ReferentialAction.Cascade);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills");

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 5);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 6);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 7);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 8);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 5);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 6);

            migrationBuilder.DeleteData(
                table: "PaymentStatus",
                keyColumn: "StatusId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "PaymentStatus",
                keyColumn: "StatusId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "PaymentStatus",
                keyColumn: "StatusId",
                keyValue: 3);

            migrationBuilder.AlterColumn<int>(
                name: "StatusId",
                table: "bills",
                type: "INTEGER",
                nullable: true,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldDefaultValue: 1);

            migrationBuilder.AlterColumn<int>(
                name: "PaymentMethodId",
                table: "bills",
                type: "INTEGER",
                nullable: true,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldDefaultValue: 1);

            migrationBuilder.AlterColumn<int>(
                name: "CategoryId",
                table: "bills",
                type: "INTEGER",
                nullable: true,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldDefaultValue: 8);

            migrationBuilder.AlterColumn<int>(
                name: "CategoryId",
                table: "BillItems",
                type: "INTEGER",
                nullable: true,
                oldClrType: typeof(int),
                oldType: "INTEGER",
                oldDefaultValue: 8);

            migrationBuilder.AddForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills",
                column: "PaymentMethodId",
                principalTable: "PaymentMethod",
                principalColumn: "PaymentId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills",
                column: "StatusId",
                principalTable: "PaymentStatus",
                principalColumn: "StatusId");
        }
    }
}
