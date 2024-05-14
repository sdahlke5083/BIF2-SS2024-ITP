using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Geld_Guardian.Migrations
{
    /// <inheritdoc />
    public partial class UserContextBill : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "UserId",
                table: "bills",
                type: "TEXT",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_bills_UserId",
                table: "bills",
                column: "UserId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_AspNetUsers_UserId",
                table: "bills",
                column: "UserId",
                principalTable: "AspNetUsers",
                principalColumn: "Id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_bills_AspNetUsers_UserId",
                table: "bills");

            migrationBuilder.DropIndex(
                name: "IX_bills_UserId",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "UserId",
                table: "bills");
        }
    }
}
