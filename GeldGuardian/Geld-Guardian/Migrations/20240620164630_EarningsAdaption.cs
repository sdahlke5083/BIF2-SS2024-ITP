using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Geld_Guardian.Migrations
{
    /// <inheritdoc />
    public partial class EarningsAdaption : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<bool>(
                name: "IsExpensesOnly",
                table: "PaymentMethod",
                type: "INTEGER",
                nullable: false,
                defaultValue: false);

            migrationBuilder.AddColumn<bool>(
                name: "EarningsInsteadOfExpenses",
                table: "Categorie",
                type: "INTEGER",
                nullable: false,
                defaultValue: false);

            migrationBuilder.AddColumn<decimal>(
                name: "Netto",
                table: "bills",
                type: "TEXT",
                nullable: true);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 1,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 2,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 3,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 4,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 5,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 6,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 7,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.UpdateData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 8,
                column: "EarningsInsteadOfExpenses",
                value: false);

            migrationBuilder.InsertData(
                table: "Categorie",
                columns: new[] { "CategorieId", "Description", "EarningsInsteadOfExpenses", "Name" },
                values: new object[,]
                {
                    { 9, null, true, "Salary" },
                    { 10, null, true, "Investment" },
                    { 11, null, true, "Other Earnings" }
                });

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 1,
                column: "IsExpensesOnly",
                value: false);

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 2,
                column: "IsExpensesOnly",
                value: true);

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 3,
                column: "IsExpensesOnly",
                value: true);

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 4,
                column: "IsExpensesOnly",
                value: false);

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 5,
                column: "IsExpensesOnly",
                value: true);

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 6,
                columns: new[] { "IsExpensesOnly", "Name" },
                values: new object[] { false, "Check" });

            migrationBuilder.InsertData(
                table: "PaymentMethod",
                columns: new[] { "PaymentId", "Description", "IsExpensesOnly", "Name" },
                values: new object[] { 7, null, true, "Other" });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 9);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 10);

            migrationBuilder.DeleteData(
                table: "Categorie",
                keyColumn: "CategorieId",
                keyValue: 11);

            migrationBuilder.DeleteData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 7);

            migrationBuilder.DropColumn(
                name: "IsExpensesOnly",
                table: "PaymentMethod");

            migrationBuilder.DropColumn(
                name: "EarningsInsteadOfExpenses",
                table: "Categorie");

            migrationBuilder.DropColumn(
                name: "Netto",
                table: "bills");

            migrationBuilder.UpdateData(
                table: "PaymentMethod",
                keyColumn: "PaymentId",
                keyValue: 6,
                column: "Name",
                value: "Other");
        }
    }
}
